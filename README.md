# -
 使用C语言的链表实现对蛇体的添加、删除、修改和查询。当蛇吃了食物后，它的长度会增加一个单位。当它到达地图的边界或它自己的时候，蛇会死亡，并在原来的地方再生出一条原来大小的小蛇。调用Linux的NCURSES库来实现游戏界面的显示和访问键盘输入上下键来控制移动。

在项目中使用了ncurses库以及多线程的一些api，所以将snake.c编译时需要加入-lpthread 和 -lncurses:

gcc snake.c -lpthread -lncurses -o snake

Enjoy the game!!!

-MADE BY ZYX
