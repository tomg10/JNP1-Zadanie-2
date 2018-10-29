!/bin/bash


DIR=$1

if [ "$2" = "-comp" ] || [ "$3" = "-comp" ]; then
	COMP=1
else
	COMP=0
fi

if [ "$2" = "-remove" ] || [ "$3" = "-remove" ]; then
	REM=1
else
	REM=0
fi


RED='\033[0;31m'
NC='\033[0m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
BLUE='\033[1;34m'
G='\033[1;33m'

INVALID_COUNT=0

if [ "$COMP" = "0" ]; then
	echo -e "${G}Checking the neccesary files...${NC}"

	set_header="$DIR/strset.h"
	set_source="$DIR/strset.cc"
	const_header="$DIR/strsetconst.h"
	const_source="$DIR/strsetconst.cc"

	if [ ! -f $set_header ] || [ ! -f $set_source ]; then
		echo -e "${RED}Some of the strset files are missing${NC}"
		exit 1
	fi

	if [ ! -f "$const_header" ] || [ ! -f $const_source ]; then
		echo -e "${RED}Some of the strsetconst files are missing${NC}"
		exit 1
	fi

	echo -e "${G}Compiling source files...${NC}"
	
	g++ -Wall -Wextra -DNDEBUG -O2 -std=c++17 -c "$set_source" -o "$DIR/strset.o"
	g++ -Wall -Wextra -DNDEBUG -O2 -std=c++17 -c "$const_source" -o "$DIR/strsetconst.o"
	

	if [ "$?" -ne 0 ]; then
		echo -e "${RED}Something went wrong during the compilation of source files${NC}"
		exit 1
	fi

	echo -e "${GREEN}Compilation successful${NC}"
else
	if [ ! -f "$DIR/strset.o" ] || [ ! -f "$DIR/strsetconst.o" ]; then
		echo -e "${RED}Objects not found for strset or strsetconst${NC}"
		exit 1
	fi
fi

echo -e "${ORANGE}-------Tests-------${NC}"

for test in $DIR/*.c*
do
	test_name="${test%.*}"
	extension="${test##*.}"
	base_name=$(basename "$test" ".$extension")

	

	if [ "$base_name" = "strset" ] || [ "$base_name" = "strsetconst" ];
	then
		continue
	fi

	echo -ne "Test ${BLUE}$base_name${NC}:"

	if [ "$extension" = "c" ]; then
		gcc -Wall -Wextra -O2 -std=c11 -c "$test_name.c" -o "$test_name.o"
	elif [ "$extension" = "cc" ]; then
		g++ -Wall -Wextra -O2 -std=c++17 -c "$test_name.cc" -o "$test_name.o"
	fi

	g++ "$test_name.o" "$DIR/strsetconst.o" "$DIR/strset.o" -o "$DIR/$base_name"

	"$DIR/$base_name" > /dev/null 2>&1

	if [ "$?" -ne 0 ]; then
		echo -e "  ${RED}INCORRECT${NC}"
		((INVALID_COUNT++))
	else
		echo -e " ${GREEN}CORRECT${NC}"
	fi

	if [ "$REM" = "1" ]; then
		rm "$test_name.o"
		rm "$DIR/$base_name"
	fi
done

echo -e "${RED}$INVALID_COUNT test(s) invalid${NC}"
