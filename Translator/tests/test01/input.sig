PROGRAM TEST1;
VAR A : INTEGER[2..8]; B : FLOAT[3..4]; C : INTEGER; D : FLOAT;
BEGIN
C := 5;
LOOP
C := B[A[D]];
B[1] := D;
LOOP
A[1] := B[A[8]];
A[5] := B[3];
ENDLOOP;
ENDLOOP;
END.
