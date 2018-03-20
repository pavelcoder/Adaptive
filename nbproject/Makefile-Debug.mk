#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/model/Chunk.o \
	${OBJECTDIR}/model/Video.o \
	${OBJECTDIR}/net/NetSpeedChange.o \
	${OBJECTDIR}/net/NetworkDownloader.o \
	${OBJECTDIR}/player/AdaptiveTrackSelector.o \
	${OBJECTDIR}/player/Player.o \
	${OBJECTDIR}/player/PlayerListener.o \
	${OBJECTDIR}/test/PlayerTester.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/adaptive

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/adaptive: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/adaptive ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/model/Chunk.o: model/Chunk.cpp
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/Chunk.o model/Chunk.cpp

${OBJECTDIR}/model/Video.o: model/Video.cpp
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/Video.o model/Video.cpp

${OBJECTDIR}/net/NetSpeedChange.o: net/NetSpeedChange.cpp
	${MKDIR} -p ${OBJECTDIR}/net
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/net/NetSpeedChange.o net/NetSpeedChange.cpp

${OBJECTDIR}/net/NetworkDownloader.o: net/NetworkDownloader.cpp
	${MKDIR} -p ${OBJECTDIR}/net
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/net/NetworkDownloader.o net/NetworkDownloader.cpp

${OBJECTDIR}/player/AdaptiveTrackSelector.o: player/AdaptiveTrackSelector.cpp
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/AdaptiveTrackSelector.o player/AdaptiveTrackSelector.cpp

${OBJECTDIR}/player/Player.o: player/Player.cpp
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/Player.o player/Player.cpp

${OBJECTDIR}/player/PlayerListener.o: player/PlayerListener.cpp
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/PlayerListener.o player/PlayerListener.cpp

${OBJECTDIR}/test/PlayerTester.o: test/PlayerTester.cpp
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/PlayerTester.o test/PlayerTester.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
