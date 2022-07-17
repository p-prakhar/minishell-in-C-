#!/bin/bash

#The option store cvf , tvf or xvf, as selected by the user
option=$1

#archiveFile stores the target file, that is the archive file.
archiveFile=$2

#This is the number input files, that is the number of files archived into the archive file
numInputFiles=$(($# - 2))

#To store meta data such as the file names and file information, the archive file would have various sections
#To mark such sections we will use codes that would uniquely identify the regions where the meta data of a certain file is

#Marks the beginning and end of the name region of a file
nameCodeB='Nuxh8RM'
nameCodeE='5f7EZz3'

#Marks the beginning and end of the details region of a file
infoCodeB='CuFJ2kU'
infoCodeE='MpSS2aW'

#Marks the beginning and end of the data region of a file
dataCodeB='m7zj2Jy'
dataCodeE='965Ub49'


#Creation of an archive file
if [[ "$option" == "cvf" ]]; then

#Taking care of the case if the file with same name already exists
    touch $archiveFile
    rm $archiveFile

    #The counter maintains the index of the file which is currently being archived
    counter=0
    for i in $*; do
        ((++counter))

        #Since the first two arguments are the name of the output file and the option chosen, we perform archiving past the second argument
        if [[ $counter -gt 2 ]]; then

        #Displaying the name of the file currently archiving
            echo $i

            #Adding the counter value to the codes make them unique for this file

            #Storing the name of the file
            echo $nameCodeB$(($counter - 2)) >>$archiveFile
            echo $i >>$archiveFile
            echo $nameCodeE$(($counter - 2)) >>$archiveFile

            #Storing the details of the file
            echo $infoCodeB$(($counter - 2)) >>$archiveFile
            ls -l $i >>$archiveFile
            echo $infoCodeE$(($counter - 2)) >>$archiveFile

            #Storing the content of the file
            echo $dataCodeB$(($counter - 2)) >>$archiveFile
            cat $i >>$archiveFile
            echo "$dataCodeE$(($counter - 2))" >>$archiveFile
        fi
    done

    #Storing the number of files present in the archive
    echo $numInputFiles >>$archiveFile

fi

#Seeing the details of the archived files
if [[ "$option" == "tvf" ]]; then

    #Extracting the number of files in the archive, as defined in the cvf part, the number of files is the last lie of the archive file
    numInputFiles=$(tail -n 1 $archiveFile)

    
    counter=1
    while [[ $counter -le $numInputFiles ]]; do

        #Printing the info code beginning and the following line, which is the details, however we dont need the code, so retaining only the details via tail utility
        grep -A1 $infoCodeB$counter $archiveFile | tail -n 1
        ((++counter))
    done
fi

#Extraction of files from the archive
if [[ "$option" == "xvf" ]]; then
    numInputFiles=$(tail -n 1 $archiveFile)
    counter=1
    while [[ $counter -le $numInputFiles ]]; do

        #Extracting the file name in similar fashion as done with details earlier
        fileName=$(grep -A1 $nameCodeB$counter $archiveFile | tail -n 1)

        #Printing the name of the file which is currently being extracted
        echo $fileName

        #Extracting the contents of the file, by checking the end point of the required data, and number of lines of data present
        dataEnds=$(($(grep -n $dataCodeE$counter $archiveFile | cut -d':' -f1) - 1))
        numLinesOfData=$(($dataEnds - $(grep -n $dataCodeB$counter $archiveFile | cut -d':' -f1)))
        cat $archiveFile | head -n $dataEnds | tail -n $numLinesOfData >$fileName
        ((++counter))
    done
fi