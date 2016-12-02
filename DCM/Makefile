SLIB = libdcm.so
EXE = dcm.exe
TARGET:${EXE} ${SLIB}
LIBS = -lpthread
CC = g++
CFLAGS = -g -Wunused
OBJ = VRF.o AbstractRouterVRF.o SSMMap.o RouterPim.o RouterOspf.o RouterBgp.o AbstractInterface.o VEInterface.o IfUtils.o ETHInterface.o AbstractL3Config.o PIMConfig.o DCM.o RouterPimCallpointWorker.o RouterOspfCallpointWorker.o VRFCallpointWorker.o RouterBgpCallpointWorker.o VEInterfaceCallpointWorker.o Rule.o PIMConfigCallpointWorker.o L3Criteria.o L2Criteria.o RESTServer.o RESTInit.o Utils.o RouterModuleGenericCallpoint.o
%.o:%.cpp
	${CC} ${CFLAGS} -c -I . $<
${EXE}:main.o ${OBJ}
	${CC} ${CFLAGS} main.o ${OBJ} -o ${EXE} ${LIBS}
${SLIB}:${OBJ}
	${CC} ${CFLAGS} ${OBJ} -shared -o ${SLIB}
clean:
	rm ${OBJ} main.o ${SLIB} ${EXE}
