# Practice 1

1. Number Summation
- publish 一個 Int32 的數字到 Topic 上，再 subscribe 組內所有人 publish 的數字，加總後印出來

```
$ rosrun practice1 number_pub1
$ rosrun practice1 number_pub2
...

$ rosrun practice1 number_sum
```

2. Turtles spawn and control
- 呼叫 turtle
```
$ roslaunch practice1 turtlesim.launch
```
- 將原本的烏龜刪掉，呼叫和組員數量相同的烏龜
```
$ rosrun practice1 turtle_spawn
```
- 控制自己名字的烏龜，在一位同學的電腦上操控
```
$ rosrun practice1 turtle_control
```

