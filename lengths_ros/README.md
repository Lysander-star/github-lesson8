# 8.1 C++ 与 CMake + 8.2 ROS2

## 1. 构建和运行的命令

8.1：
    cd ~/lesson8
    cmake -S . -B build && cmake --build build
    ./build/test_lengths        # 全部 PASS 时退出码 0，有 FAIL 时返回 1

8.2：
    cd ~/ros2_ws
    source /opt/ros/humble/setup.bash
    colcon build --packages-select lengths_ros

    # 每个终端都要先执行这三行
    source /opt/ros/humble/setup.bash
    source ~/ros2_ws/install/setup.bash
    export ROS_LOCALHOST_ONLY=1
    ros2 run lengths_ros length_pub    # 终端 A
    ros2 run lengths_ros mean_node     # 终端 B

## 2. 节点名 / 话题名 / 消息类型

| 节点名 | 角色 | 话题 | 消息类型 |
|---|---|---|---|
| length_pub | 发布 | /lengths | example_interfaces/msg/Float64MultiArray |
| mean_node | 订阅 /lengths，发布 /mean_length | /mean_length | example_interfaces/msg/Float64 |

发布节点每秒按 4 个 → 3 个 → 空 → 5 个轮转，输入与输出对应：

| 输入 | mean_node 输出 |
|---|---|
| [1.0, 2.0, 3.0, 4.0] | 2.5 |
| [2.0, 4.0, 6.0] | 4.0 |
| [] 空数组 | 不发布，只打印 empty input 日志 |
| [5.0, 5.0, 5.0, 5.0, 5.0] | 5.0 |

实测 ros2 topic echo /mean_length 只出现 2.5、4.0、5.0 三个值循环，空数组那一拍没有任何输出。

## 3. 为什么空数组的均值不能返回 0

第一，空数组的均值在数学上没有定义，是 0 个元素除以 0，返回 0 等于给一个不存在的答案编造了数值。

第二，0 本身是完全合法的均值结果，例如 [-1.0, 1.0] 的均值就是 0。空数组也返回 0 的话，下游节点无法区分"算出来确实是 0"和"根本没算出来"这两种情况。

所以返回类型用 std::optional<double>，空数组时返回 std::nullopt，把"没有值"本身表达出来，而不是用假数字冒充。

## 4. 遇到的问题和解决方案

- colcon 没有安装：执行时提示"未找到命令"，用 sudo apt install -y python3-colcon-common-extensions 装上，且要重开终端才生效。
- 长命令粘贴进终端没有反应：Ubuntu 终端粘贴是 Ctrl+Shift+V 不是 Ctrl+V。改成一次只写一个文件，并用 wc -l 核对行数确认没被截断。
- 运行 ./build/test_lengths 报"没有那个文件或目录"、退出码 127：build 目录由 cmake -S . -B build 生成，必须先配置再编译，不能跳过构建。
- 担心收到同实验室他人节点的数据：每个终端先 export ROS_LOCALHOST_ONLY=1，只在本机通信。
