.PHONY: clean All

All:
	@echo "----------Building project:[ ica-master - Debug ]----------"
	@"$(MAKE)" -f  "ica-master.mk"
clean:
	@echo "----------Cleaning project:[ ica-master - Debug ]----------"
	@"$(MAKE)" -f  "ica-master.mk" clean
