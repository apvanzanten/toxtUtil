.PHONY: release debug clean

release: release/Makefile
	@cd release; $(MAKE) --no-print-directory all

debug: debug/Makefile
	@cd debug; $(MAKE) --no-print-directory all

release/Makefile: CMakeLists.txt
	@mkdir -p release; cd release; cmake -DCMAKE_BUILD_TYPE=Release ../

debug/Makefile: CMakeLists.txt
	@mkdir -p debug; cd debug; cmake -DCMAKE_BUILD_TYPE=Debug ../

clean:
	@rm -rf release debug
