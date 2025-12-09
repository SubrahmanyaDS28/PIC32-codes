#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/FreeRTOS_project1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/FreeRTOS_project1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../main.c ../RTOS_Kernel/source/heap_4.c ../RTOS_Kernel/source/list.c ../RTOS_Kernel/source/port.c ../RTOS_Kernel/source/port_asm.S ../RTOS_Kernel/source/queue.c ../RTOS_Kernel/source/tasks.c ../RTOS_Kernel/source/timers.c ../RTOS_Lib/freertos_hooks.c ../RTOS_Lib/rtos_dynamic_demo.c ../RTOS_Lib/rtos_mutex_demo.c ../RTOS_Lib/rtos_semaphore_demo.c ../RTOS_Lib/rtos_uart.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1535642141/heap_4.o ${OBJECTDIR}/_ext/1535642141/list.o ${OBJECTDIR}/_ext/1535642141/port.o ${OBJECTDIR}/_ext/1535642141/port_asm.o ${OBJECTDIR}/_ext/1535642141/queue.o ${OBJECTDIR}/_ext/1535642141/tasks.o ${OBJECTDIR}/_ext/1535642141/timers.o ${OBJECTDIR}/_ext/202601915/freertos_hooks.o ${OBJECTDIR}/_ext/202601915/rtos_dynamic_demo.o ${OBJECTDIR}/_ext/202601915/rtos_mutex_demo.o ${OBJECTDIR}/_ext/202601915/rtos_semaphore_demo.o ${OBJECTDIR}/_ext/202601915/rtos_uart.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1535642141/heap_4.o.d ${OBJECTDIR}/_ext/1535642141/list.o.d ${OBJECTDIR}/_ext/1535642141/port.o.d ${OBJECTDIR}/_ext/1535642141/port_asm.o.d ${OBJECTDIR}/_ext/1535642141/queue.o.d ${OBJECTDIR}/_ext/1535642141/tasks.o.d ${OBJECTDIR}/_ext/1535642141/timers.o.d ${OBJECTDIR}/_ext/202601915/freertos_hooks.o.d ${OBJECTDIR}/_ext/202601915/rtos_dynamic_demo.o.d ${OBJECTDIR}/_ext/202601915/rtos_mutex_demo.o.d ${OBJECTDIR}/_ext/202601915/rtos_semaphore_demo.o.d ${OBJECTDIR}/_ext/202601915/rtos_uart.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1535642141/heap_4.o ${OBJECTDIR}/_ext/1535642141/list.o ${OBJECTDIR}/_ext/1535642141/port.o ${OBJECTDIR}/_ext/1535642141/port_asm.o ${OBJECTDIR}/_ext/1535642141/queue.o ${OBJECTDIR}/_ext/1535642141/tasks.o ${OBJECTDIR}/_ext/1535642141/timers.o ${OBJECTDIR}/_ext/202601915/freertos_hooks.o ${OBJECTDIR}/_ext/202601915/rtos_dynamic_demo.o ${OBJECTDIR}/_ext/202601915/rtos_mutex_demo.o ${OBJECTDIR}/_ext/202601915/rtos_semaphore_demo.o ${OBJECTDIR}/_ext/202601915/rtos_uart.o

# Source Files
SOURCEFILES=../main.c ../RTOS_Kernel/source/heap_4.c ../RTOS_Kernel/source/list.c ../RTOS_Kernel/source/port.c ../RTOS_Kernel/source/port_asm.S ../RTOS_Kernel/source/queue.c ../RTOS_Kernel/source/tasks.c ../RTOS_Kernel/source/timers.c ../RTOS_Lib/freertos_hooks.c ../RTOS_Lib/rtos_dynamic_demo.c ../RTOS_Lib/rtos_mutex_demo.c ../RTOS_Lib/rtos_semaphore_demo.c ../RTOS_Lib/rtos_uart.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/FreeRTOS_project1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MK1024MCM100
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1535642141/port_asm.o: ../RTOS_Kernel/source/port_asm.S  .generated_files/flags/default/aa340c1af5eac4b6eb089234c4ec66d20c304d42 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1535642141" 
	@${RM} ${OBJECTDIR}/_ext/1535642141/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1535642141/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1535642141/port_asm.o.ok ${OBJECTDIR}/_ext/1535642141/port_asm.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -MMD -MF "${OBJECTDIR}/_ext/1535642141/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1535642141/port_asm.o ../RTOS_Kernel/source/port_asm.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1535642141/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1 -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1535642141/port_asm.o.d" "${OBJECTDIR}/_ext/1535642141/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1535642141/port_asm.o: ../RTOS_Kernel/source/port_asm.S  .generated_files/flags/default/4d1ace04d41835d55f46f806de366b4e97d0430e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1535642141" 
	@${RM} ${OBJECTDIR}/_ext/1535642141/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1535642141/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1535642141/port_asm.o.ok ${OBJECTDIR}/_ext/1535642141/port_asm.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -MMD -MF "${OBJECTDIR}/_ext/1535642141/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1535642141/port_asm.o ../RTOS_Kernel/source/port_asm.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1535642141/port_asm.o.asm.d",--gdwarf-2 -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1535642141/port_asm.o.d" "${OBJECTDIR}/_ext/1535642141/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/default/fbce9fee439716d1ecee2e7e0b3e007dbba61a0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1535642141/heap_4.o: ../RTOS_Kernel/source/heap_4.c  .generated_files/flags/default/45e5caf52cc0090f6b27aade51303c9c050e2f2d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1535642141" 
	@${RM} ${OBJECTDIR}/_ext/1535642141/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1535642141/heap_4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/1535642141/heap_4.o.d" -o ${OBJECTDIR}/_ext/1535642141/heap_4.o ../RTOS_Kernel/source/heap_4.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1535642141/list.o: ../RTOS_Kernel/source/list.c  .generated_files/flags/default/3c882755fc1debeccd59be1a820714d1745142cb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1535642141" 
	@${RM} ${OBJECTDIR}/_ext/1535642141/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1535642141/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/1535642141/list.o.d" -o ${OBJECTDIR}/_ext/1535642141/list.o ../RTOS_Kernel/source/list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1535642141/port.o: ../RTOS_Kernel/source/port.c  .generated_files/flags/default/ce29d281d8579c9fd2ae44599bf2f2dee91d2650 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1535642141" 
	@${RM} ${OBJECTDIR}/_ext/1535642141/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1535642141/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/1535642141/port.o.d" -o ${OBJECTDIR}/_ext/1535642141/port.o ../RTOS_Kernel/source/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1535642141/queue.o: ../RTOS_Kernel/source/queue.c  .generated_files/flags/default/31ff1f09611bc3f78f6e93300a52e92f3a207c32 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1535642141" 
	@${RM} ${OBJECTDIR}/_ext/1535642141/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1535642141/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/1535642141/queue.o.d" -o ${OBJECTDIR}/_ext/1535642141/queue.o ../RTOS_Kernel/source/queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1535642141/tasks.o: ../RTOS_Kernel/source/tasks.c  .generated_files/flags/default/32d970a56b4585b3282b765976c6c4f1363536be .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1535642141" 
	@${RM} ${OBJECTDIR}/_ext/1535642141/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1535642141/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/1535642141/tasks.o.d" -o ${OBJECTDIR}/_ext/1535642141/tasks.o ../RTOS_Kernel/source/tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1535642141/timers.o: ../RTOS_Kernel/source/timers.c  .generated_files/flags/default/45d0fefd25df125f74041e3f4cb3dd3f80e52939 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1535642141" 
	@${RM} ${OBJECTDIR}/_ext/1535642141/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1535642141/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/1535642141/timers.o.d" -o ${OBJECTDIR}/_ext/1535642141/timers.o ../RTOS_Kernel/source/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/202601915/freertos_hooks.o: ../RTOS_Lib/freertos_hooks.c  .generated_files/flags/default/4428bd9f46738de43217e4d6299d8c4203828cc6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/202601915" 
	@${RM} ${OBJECTDIR}/_ext/202601915/freertos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/202601915/freertos_hooks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/202601915/freertos_hooks.o.d" -o ${OBJECTDIR}/_ext/202601915/freertos_hooks.o ../RTOS_Lib/freertos_hooks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/202601915/rtos_dynamic_demo.o: ../RTOS_Lib/rtos_dynamic_demo.c  .generated_files/flags/default/724fe0f0a3f4581a9f8d4b70da80832e9007fc89 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/202601915" 
	@${RM} ${OBJECTDIR}/_ext/202601915/rtos_dynamic_demo.o.d 
	@${RM} ${OBJECTDIR}/_ext/202601915/rtos_dynamic_demo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/202601915/rtos_dynamic_demo.o.d" -o ${OBJECTDIR}/_ext/202601915/rtos_dynamic_demo.o ../RTOS_Lib/rtos_dynamic_demo.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/202601915/rtos_mutex_demo.o: ../RTOS_Lib/rtos_mutex_demo.c  .generated_files/flags/default/ce97f91ce3a912f8d245d5045034bf8c7a48b5ae .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/202601915" 
	@${RM} ${OBJECTDIR}/_ext/202601915/rtos_mutex_demo.o.d 
	@${RM} ${OBJECTDIR}/_ext/202601915/rtos_mutex_demo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/202601915/rtos_mutex_demo.o.d" -o ${OBJECTDIR}/_ext/202601915/rtos_mutex_demo.o ../RTOS_Lib/rtos_mutex_demo.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/202601915/rtos_semaphore_demo.o: ../RTOS_Lib/rtos_semaphore_demo.c  .generated_files/flags/default/b00898ef069f37d1169e08fed44b7f4691c00644 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/202601915" 
	@${RM} ${OBJECTDIR}/_ext/202601915/rtos_semaphore_demo.o.d 
	@${RM} ${OBJECTDIR}/_ext/202601915/rtos_semaphore_demo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/202601915/rtos_semaphore_demo.o.d" -o ${OBJECTDIR}/_ext/202601915/rtos_semaphore_demo.o ../RTOS_Lib/rtos_semaphore_demo.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/202601915/rtos_uart.o: ../RTOS_Lib/rtos_uart.c  .generated_files/flags/default/939b003593d0019b03d867044dca4b87ea85c07 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/202601915" 
	@${RM} ${OBJECTDIR}/_ext/202601915/rtos_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/202601915/rtos_uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/202601915/rtos_uart.o.d" -o ${OBJECTDIR}/_ext/202601915/rtos_uart.o ../RTOS_Lib/rtos_uart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/default/ede306b802f90bcc91892408332b3434de14ac2b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1535642141/heap_4.o: ../RTOS_Kernel/source/heap_4.c  .generated_files/flags/default/fb72172b8cc2448191436d3048777c7f98b3797b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1535642141" 
	@${RM} ${OBJECTDIR}/_ext/1535642141/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1535642141/heap_4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/1535642141/heap_4.o.d" -o ${OBJECTDIR}/_ext/1535642141/heap_4.o ../RTOS_Kernel/source/heap_4.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1535642141/list.o: ../RTOS_Kernel/source/list.c  .generated_files/flags/default/48fe5f4faf2e69d011c293e79a45f23fa2e86f7e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1535642141" 
	@${RM} ${OBJECTDIR}/_ext/1535642141/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1535642141/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/1535642141/list.o.d" -o ${OBJECTDIR}/_ext/1535642141/list.o ../RTOS_Kernel/source/list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1535642141/port.o: ../RTOS_Kernel/source/port.c  .generated_files/flags/default/3c7fb305afc2684f97e836901ef64b9a68a18c0b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1535642141" 
	@${RM} ${OBJECTDIR}/_ext/1535642141/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1535642141/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/1535642141/port.o.d" -o ${OBJECTDIR}/_ext/1535642141/port.o ../RTOS_Kernel/source/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1535642141/queue.o: ../RTOS_Kernel/source/queue.c  .generated_files/flags/default/bdbaa393e6a5f453a0505860f87f5f7d2d0697f8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1535642141" 
	@${RM} ${OBJECTDIR}/_ext/1535642141/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1535642141/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/1535642141/queue.o.d" -o ${OBJECTDIR}/_ext/1535642141/queue.o ../RTOS_Kernel/source/queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1535642141/tasks.o: ../RTOS_Kernel/source/tasks.c  .generated_files/flags/default/bfc983f8aecba497c0c80aba35dc998042570389 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1535642141" 
	@${RM} ${OBJECTDIR}/_ext/1535642141/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1535642141/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/1535642141/tasks.o.d" -o ${OBJECTDIR}/_ext/1535642141/tasks.o ../RTOS_Kernel/source/tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1535642141/timers.o: ../RTOS_Kernel/source/timers.c  .generated_files/flags/default/a59b4d792df30b89177db348069a8b419522ae06 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1535642141" 
	@${RM} ${OBJECTDIR}/_ext/1535642141/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1535642141/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/1535642141/timers.o.d" -o ${OBJECTDIR}/_ext/1535642141/timers.o ../RTOS_Kernel/source/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/202601915/freertos_hooks.o: ../RTOS_Lib/freertos_hooks.c  .generated_files/flags/default/806fb704926440f95b56bbcbd0b7a62cde2d07c9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/202601915" 
	@${RM} ${OBJECTDIR}/_ext/202601915/freertos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/202601915/freertos_hooks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/202601915/freertos_hooks.o.d" -o ${OBJECTDIR}/_ext/202601915/freertos_hooks.o ../RTOS_Lib/freertos_hooks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/202601915/rtos_dynamic_demo.o: ../RTOS_Lib/rtos_dynamic_demo.c  .generated_files/flags/default/c927f9312a0dfb392eb39ad20abac42f7f99a306 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/202601915" 
	@${RM} ${OBJECTDIR}/_ext/202601915/rtos_dynamic_demo.o.d 
	@${RM} ${OBJECTDIR}/_ext/202601915/rtos_dynamic_demo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/202601915/rtos_dynamic_demo.o.d" -o ${OBJECTDIR}/_ext/202601915/rtos_dynamic_demo.o ../RTOS_Lib/rtos_dynamic_demo.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/202601915/rtos_mutex_demo.o: ../RTOS_Lib/rtos_mutex_demo.c  .generated_files/flags/default/f7285d61ddc56fe6b5925c93b7bc9e6513e0721e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/202601915" 
	@${RM} ${OBJECTDIR}/_ext/202601915/rtos_mutex_demo.o.d 
	@${RM} ${OBJECTDIR}/_ext/202601915/rtos_mutex_demo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/202601915/rtos_mutex_demo.o.d" -o ${OBJECTDIR}/_ext/202601915/rtos_mutex_demo.o ../RTOS_Lib/rtos_mutex_demo.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/202601915/rtos_semaphore_demo.o: ../RTOS_Lib/rtos_semaphore_demo.c  .generated_files/flags/default/7f5c760c6bc6db037683df4f5ee4acafb9aa1f10 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/202601915" 
	@${RM} ${OBJECTDIR}/_ext/202601915/rtos_semaphore_demo.o.d 
	@${RM} ${OBJECTDIR}/_ext/202601915/rtos_semaphore_demo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/202601915/rtos_semaphore_demo.o.d" -o ${OBJECTDIR}/_ext/202601915/rtos_semaphore_demo.o ../RTOS_Lib/rtos_semaphore_demo.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/202601915/rtos_uart.o: ../RTOS_Lib/rtos_uart.c  .generated_files/flags/default/3648ed5ddb2e3940aebb539d7ef0e463280088d1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/202601915" 
	@${RM} ${OBJECTDIR}/_ext/202601915/rtos_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/202601915/rtos_uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Kernel/include" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/RTOS_Lib" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1/Drivers" -I"/media/Data/MPLAB_Project/FreeRTOS_projects/app1" -MP -MMD -MF "${OBJECTDIR}/_ext/202601915/rtos_uart.o.d" -o ${OBJECTDIR}/_ext/202601915/rtos_uart.o ../RTOS_Lib/rtos_uart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/FreeRTOS_project1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/FreeRTOS_project1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x36F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/FreeRTOS_project1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/FreeRTOS_project1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}/xc32-bin2hex ${DISTDIR}/FreeRTOS_project1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
