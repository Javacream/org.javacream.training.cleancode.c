# Zentraler Einstiegspunkt fuer alle Schulungsbeispiele.
.PHONY: test clean

test:
	@total=0; passed=0; failed=0; failed_dirs=''; \
	for file in $$(find blocks refactoring -name Makefile -type f -print | LC_ALL=C sort); do \
	  dir=$${file%/Makefile}; \
	  total=$$((total + 1)); \
	  printf '\n=== Test: %s ===\n' "$$dir"; \
	  if $(MAKE) -C "$$dir" test; then \
	    passed=$$((passed + 1)); \
	  else \
	    failed=$$((failed + 1)); \
	    failed_dirs="$$failed_dirs $$dir"; \
	  fi; \
	done; \
	printf '\n=== Testzusammenfassung ===\nBeispielverzeichnisse: %s\nErfolgreich: %s\nFehlgeschlagen: %s\n' "$$total" "$$passed" "$$failed"; \
	if [ "$$failed" -ne 0 ]; then \
	  printf 'Fehlerhafte Verzeichnisse:\n'; \
	  for dir in $$failed_dirs; do printf '  %s\n' "$$dir"; done; \
	  exit 1; \
	fi

clean:
	@set -e; \
	find blocks refactoring -name Makefile -type f -print | LC_ALL=C sort | while IFS= read -r file; do \
	  dir=$${file%/Makefile}; \
	  printf "\n=== Clean: %s ===\n" "$$dir"; \
	  $(MAKE) -C "$$dir" clean || exit $$?; \
	done
