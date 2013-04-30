# Generated automatically from Makefile.in by configure.



DEST=/etc/nportredird
CONF_FILE=nportredird.conf
EFILE=nportredird
SRCDIR=src

_BC="[1\;1\;36m"
_C="[1\;0\;36m"
__C="[1\;7\;36m"
_E="[0m"

all default portredird:
	@cd $(SRCDIR); $(MAKE)


dist distclean cleanall: clean confclean

clean:
	@echo "${__C}                                                     ${_E}"
	@echo " ${_BC}Cleaning stuff and things...${_E}"
	@echo "${__C}                                                      ${_E}"
	@if [ -e $(SRCDIR)/Makefile ]; then \
      cd $(SRCDIR); $(MAKE) clean; \
     fi

confclean:
	@rm -rf Makefile ./src/Makefile \
                config.cache config.log config.status ./src/include/config.h
	@rm -rf include/config.h; \
	rm -rf src/configparse.[hc]; \
	rm -rf src/include/configparse.h; \
	touch src/include/configparse.h

                

install:
	@echo "${__C}                                                      ${_E}"
	@echo " ${_BC}Installing ${EFILE}...${_E}"
	@echo "${__C}                                                      ${_E}"
	@echo 
	@if test ! -d $(DEST); then \
		echo "${_BC}Creating directory $(DEST)...${_E}"; \
		mkdir $(DEST); \
	else \
		echo "${_BC}Configuration directory already exists...${_E}"; \
	fi
	@if test ! -r $(DEST)/$(CONF_FILE); then \
		echo "${_BC}Copying sample configuration file...${_E}"; \
		cp ./etc/$(CONF_FILE) $(DEST)/; \
	else \
		echo "${_BC}Sample configuration file not copied.${_E}"; \
	fi
	@echo "${_BC}Copying binary to /usr/local/bin...${_E}";
	@cp ./bin/nportredird /usr/local/bin;
	@echo "${_BC}Installing man page under section 8...${_E}";
	@cp ./doc/nportredird.8 /usr/local/man/man8;

