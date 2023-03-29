
import os, shutil
import subprocess as sp
import argparse as ap

libfoundation_root = os.getcwd()


def clean():

    build_dir = os.path.join(libfoundation_root, 'build')
    if os.path.isdir(build_dir):
        print('>> deleting %s' % build_dir)
        shutil.rmtree(build_dir)

    print('>> making %s' % build_dir)
    os.mkdir(build_dir)


def compile(build_type: str):

    assert shutil.which('clang'), 'clang not in path'
    assert shutil.which('clang++'), 'clang++ not in path'
    assert shutil.which('cmake'), 'cmake not in path'
    assert shutil.which('ninja'), 'ninja not in path'
    assert shutil.which('vcpkg'), 'vcpkg not in path'

    vcpkg_root = os.environ['VCPKG_ROOT']
    cmake_toolchain_file = os.path.join(vcpkg_root, 'scripts', 'buildsystems', 'vcpkg.cmake')

    if build_type == 'All' or build_type == 'Release':

        build_dir = os.path.join(libfoundation_root, 'build', 'release')
        print('>> Making directory %s' % (build_dir))
        if not os.path.isdir(build_dir):
            os.mkdir(build_dir)

        cmake_cmd = ['cmake', 
                    '-DCMAKE_CXX_COMPILER=clang++', 
                    '-DCMAKE_BUILD_TYPE=Release',
                    '-DCMAKE_EXPORT_COMPILE_COMMANDS=ON', 
                    '-DCMAKE_TOOLCHAIN_FILE='+cmake_toolchain_file, 
                    '-S %s' % libfoundation_root, 
                    '-B %s' % build_dir]

        print('>> Running CMake with arguments:\n')
        for i in range(1, len(cmake_cmd)):
            print('\t%s' % cmake_cmd[i]) 
        sp.run(cmake_cmd)    
    
        print('>> Running Cmake with arguments:\n')
        print('--build %s' % build_dir) 
        sp.run(['cmake', '--build', build_dir])

    if build_type == 'All' or build_type == 'Debug':

        build_dir = os.path.join(libfoundation_root, 'build', 'debug')
        print('>> Making directory %s' % (build_dir))
        if not os.path.isdir(build_dir):
            os.mkdir(build_dir)


        cmake_cmd = ['cmake', 
                    '-DCMAKE_CXX_COMPILER=clang++', 
                    '-DCMAKE_BUILD_TYPE=Debug',
                    '-DCMAKE_EXPORT_COMPILE_COMMANDS=ON', 
                    '-DCMAKE_TOOLCHAIN_FILE='+cmake_toolchain_file, 
                    '-S %s' % libfoundation_root, 
                    '-B %s' % build_dir]

        print('>> Running CMake with arguments:\n')
        for i in range(1, len(cmake_cmd)):
            print('\t%s' % cmake_cmd[i]) 
        sp.run(cmake_cmd)    
    
        print('>> Running Cmake with arguments:\n')
        print('--build %s' % build_dir) 
        sp.run(['cmake', '--build', build_dir])


def run_test(build_type: str):

    program = os.path.join(libfoundation_root, 'build', build_type.lower(), 'libfoundation', 'foundation-tests')
    sp.run([program])

def run_benchmark(build_type: str):

    program = os.path.join(libfoundation_root, 'build', build_type.lower(), 'libfoundation', 'foundation-bechmarks')
    sp.run([program])




def main():

    # top level parser 
    parser = ap.ArgumentParser(prog = 'foundry',
                                     description = 'source management and build system for the libfoundation project')
    subparsers = parser.add_subparsers(title = 'foundary sub-commands',
                        dest = 'cmd')

    # clean parser
    clean_parser = subparsers.add_parser('clean', help='cleans the build directories')    
    # compile parser
    compiler_parse = subparsers.add_parser('compile', help = 'compiles the library')
    compiler_parse.add_argument('build_type', choices=['Release', 'Debug', 'All'], help='build type to compile')    
    # run test parser
    run_test_parser = subparsers.add_parser('run_test', help = 'Runs the tests')
    run_test_parser.add_argument('build_type', choices=['Release', 'Debug'], help = 'Choose between running the tests in debug mode or release mode')    
    # run benchmark parser
    run_benchmark_parser = subparsers.add_parser('run_benchmarks', help = 'Run the benchmarks')
    run_benchmark_parser.add_argument('build_type',  choices=['Release', 'Debug'], help = 'Choose between running the tests in debug mode or release mode'  )


    

    args = parser.parse_args()
    if(args.cmd == 'clean'):
        clean()
    elif(args.cmd == 'compile'):
        compile(args.build_type)
    elif(args.cmd == 'run_test'):
        run_test(args.build_type)
    elif(args.cmd == 'run_benchmark'):
        run_benchmark(args.build_type)


    


if __name__ == '__main__':
    main()



