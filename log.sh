DATE=`date '+%Y-%m-%d %H:%M:%S'`
ENTRY="$1 -- $DATE\n$2\n"

if [ $# -eq 2 ]; then
    if [ ! -e DEVLOG ]; then
        touch DEVLOG
    fi
    echo -e "$ENTRY" >> DEVLOG
else
    echo -e "Incorrect number of arguments supplied\nUsage: $ ./log.sh <firstL> <message>"  
fi
