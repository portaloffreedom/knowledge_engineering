
set (CURRENT_DIR "src/data")

set (knowledge_engineering_QT_HEADERS ${knowledge_engineering_QT_HEADERS}
        ${CURRENT_DIR}/measurements/Exercise.h
        ${CURRENT_DIR}/measurements/Measurement.h
        ${CURRENT_DIR}/measurements/DefendingMeasurement.h
        ${CURRENT_DIR}/measurements/DribblingMeasurement.h
        ${CURRENT_DIR}/measurements/PaceMeasurement.h
        ${CURRENT_DIR}/measurements/PassingMeasurement.h
        ${CURRENT_DIR}/measurements/PhysicalMeasurement.h
        ${CURRENT_DIR}/measurements/ShootingMeasurement.h
        ${CURRENT_DIR}/Class.h
        ${CURRENT_DIR}/Defending.h
        ${CURRENT_DIR}/Dribbling.h
        ${CURRENT_DIR}/Pace.h
        ${CURRENT_DIR}/Passing.h
        ${CURRENT_DIR}/Physical.h
        ${CURRENT_DIR}/Player.h
        ${CURRENT_DIR}/Shooting.h
        ${CURRENT_DIR}/Statistic.h
        PARENT_SCOPE
        )


set(knowledge_engineering_SRCS ${knowledge_engineering_SRCS}
        ${CURRENT_DIR}/measurements/Exercise.cpp
        ${CURRENT_DIR}/measurements/Measurement.cpp
        ${CURRENT_DIR}/measurements/DefendingMeasurement.cpp
        ${CURRENT_DIR}/measurements/DribblingMeasurement.cpp
        ${CURRENT_DIR}/measurements/PaceMeasurement.cpp
        ${CURRENT_DIR}/measurements/PassingMeasurement.cpp
        ${CURRENT_DIR}/measurements/PhysicalMeasurement.cpp
        ${CURRENT_DIR}/measurements/ShootingMeasurement.cpp
        ${CURRENT_DIR}/Class.cpp
        ${CURRENT_DIR}/Defending.cpp
        ${CURRENT_DIR}/Dribbling.cpp
        ${CURRENT_DIR}/Pace.cpp
        ${CURRENT_DIR}/Passing.cpp
        ${CURRENT_DIR}/Physical.cpp
        ${CURRENT_DIR}/Player.cpp
        ${CURRENT_DIR}/Shooting.cpp
        ${CURRENT_DIR}/Statistic.cpp
        PARENT_SCOPE
        )
