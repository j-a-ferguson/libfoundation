
deactivate(){
	
	PS1=$OLD_PS1
	unset OLD_PS1
	unsetenv LIBFOUNDATION_HOME
	unalias dev
}

OLD_PS1=$PS1
export PS1="(dev) $PS1"
export LIBDOUNDATION_HOME=$(pwd)
alias dev="python3 ${LIBDOUNDATION_HOME}/scripts/dev.py"
