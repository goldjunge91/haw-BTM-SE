project(src)

set(SOURCE_FILES
        fsm.cpp fsm.h
        factory.cpp factory.h
        FestoProcessAccess.cpp FestoProcessAccess.h
        minilab1008processimage.cpp minilab1008processimage.h
        FestoProcessActuators.h
        FestoProcessSensors.h
        iomasks.h
        plugin.h
        processimage.h
        plugin/defectDetector.h
        plugin/defectDetector.cpp


        ## Hier neue Dateien hinzufügen
)

add_library(src STATIC ${SOURCE_FILES})