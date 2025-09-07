################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c2000_18.12.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Hsieh/workspace_v9/digital_input_output_sixstep" --include_path="C:/Users/Hsieh/workspace_v9/digital_input_output_sixstep/Common" --include_path="C:/Users/Hsieh/workspace_v9/digital_input_output_sixstep/Header" --include_path="C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c2000_18.12.1.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c2000_18.12.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Hsieh/workspace_v9/digital_input_output_sixstep" --include_path="C:/Users/Hsieh/workspace_v9/digital_input_output_sixstep/Common" --include_path="C:/Users/Hsieh/workspace_v9/digital_input_output_sixstep/Header" --include_path="C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c2000_18.12.1.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_CpuTimers.obj: C:/ti/controlSUITE/device_support/F2837xD/v100/F2837xD_common/source/F2837xD_CpuTimers.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c2000_18.12.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Hsieh/workspace_v9/digital_input_output_sixstep" --include_path="C:/Users/Hsieh/workspace_v9/digital_input_output_sixstep/Common" --include_path="C:/Users/Hsieh/workspace_v9/digital_input_output_sixstep/Header" --include_path="C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c2000_18.12.1.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_EPwm.obj: C:/ti/controlSUITE/device_support/F2837xD/v100/F2837xD_common/source/F2837xD_EPwm.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c2000_18.12.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Hsieh/workspace_v9/digital_input_output_sixstep" --include_path="C:/Users/Hsieh/workspace_v9/digital_input_output_sixstep/Common" --include_path="C:/Users/Hsieh/workspace_v9/digital_input_output_sixstep/Header" --include_path="C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c2000_18.12.1.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


