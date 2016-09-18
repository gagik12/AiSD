set PROGRAM="%~1"

%PROGRAM% input\in1.txt > output\out1.txt

%PROGRAM% input\in2.txt > output\out2.txt

%PROGRAM% input\in3.txt > output\out3.txt

%PROGRAM% input\in4.txt > output\out4.txt

%PROGRAM% input\in5.txt > output\out5.txt

%PROGRAM% input\in6.txt > output\out6.txt

%PROGRAM% input\in7.txt > output\out7.txt

%PROGRAM% input\in8.txt > output\out8.txt

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1