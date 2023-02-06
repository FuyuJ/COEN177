# Name: <Marianne Yamazaki Dorr> 
# Date: <9/23/2021> (the day you have lab) 
# Title: Lab1 – Unix/Linux Commands and Basic Shell Programming 
# Description: This program first checks to see if user's name matches the given name.
# If it is correct, the program will then calculate the area of a circle by getting
# the radius from the user. 
#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
echo "Please enter your name:"
read name
numusers=`who | wc -l`
echo "Hi $name! There are $numusers users logged on."
if [ $name = "Marianne" ]
then
        echo "Now you can proceed!"
else
        echo "Check who logged in!"
        exit 1 
fi
response="Yes"
while [ $response != "No" ]
do
   echo "Enter radius of circle: "
   read radius
   area=`echo "$radius * $radius * 3.14" | bc` 
   echo "The area of the circle is $area"
   echo "Would you like to repeat for another circle [Yes/No]?"
        read response
done

