.PHONY: clean All

All:
	@echo "----------Building project:[ cameraRuler - Debug ]----------"
	@"$(MAKE)" -f  "cameraRuler.mk"
clean:
	@echo "----------Cleaning project:[ cameraRuler - Debug ]----------"
	@"$(MAKE)" -f  "cameraRuler.mk" clean
