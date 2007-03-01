SUBDIRS = SIM-20020503 SIM-20020118 \
          SIM-20011116 SIM-20011005 SIM-20010914 SIM-20010824 SIM-20010803

app-bundles:
	@case $(target_os) in darwin* ) \
	  echo "Making Mac OS X application bundles in coin-competitions"; \
	  for dir in $(SUBDIRS); do \
	    (cd $$dir; $(MAKE) app-bundles;) \
	  done ;; \
	esac
