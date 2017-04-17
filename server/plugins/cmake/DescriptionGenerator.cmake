execute_process(COMMAND
        python ${CMAKE_CURRENT_LIST_DIR}/descriptionGenerator.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/generated
        ${PLUGIN_TYPE}.${PLUGIN_NAME}
        ${PLUGIN_ID}
        )
