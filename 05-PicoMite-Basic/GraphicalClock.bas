Date$ = "2022-04-05"
Time$ = "20:21:00"
CLS
Box 0, 0, MM.HRes - 1, MM.VRes / 2, 3
Do
  Text MM.HRes / 2, MM.VRes / 4, Time$, "CM", 1, 1
  Text MM.HRes / 2, MM.VRes * 3 / 4, Date$, "CM", 1, 1
Loop