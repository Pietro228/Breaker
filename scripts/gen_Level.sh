if [ -z "$1" ] || [ -z "$2" ]; then
    echo "Usage: $0 <Name> <ID>"
    exit 1
fi

NAME=$1
ID=$2
NAME_NCAPITAL=$(echo "$(tr '[:upper:]' '[:lower:]' <<< "${NAME:0:1}")${NAME:1}")
HEADER_FILE="${NAME_NCAPITAL}.h"
SOURCE_FILE="${NAME_NCAPITAL}.c"

cat << EOT >> ../include/$HEADER_FILE
#pragma once

#include "level.h"

DEFINE_LEVEL(${NAME});
EOT

cat << EOT >> ../src/$SOURCE_FILE
#include "${NAME_NCAPITAL}.h"

#include "engineCore.h"

Level ${NAME} = {.id = ${ID}, .name = "${NAME}", .event_loaded = &_${NAME}_loaded};

void _${NAME}_loaded() {

}
EOT

echo "Generated \"${HEADER_FILE}\" and \"${SOURCE_FILE}\"."