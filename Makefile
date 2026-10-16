# Zentraler Einstiegspunkt fuer alle Schulungsbeispiele.
.PHONY: test
test:
	@set -e; \
	find dirty clean refactoring -name Makefile -type f -print | LC_ALL=C sort | while IFS= read -r file; do \
	  dir=$${file%/Makefile}; \
	  printf "\n=== Test: %s ===\n" "$$dir"; \
	  $(MAKE) -C "$$dir" test || exit $$?; \
	done
