## ROS implement of QXWZ NTRIP service 
ROS C++ node for qxwz linux SDK

This ROS node subscribe GPGGA topic(ie. from GPS driver node, 1Hz recommended) and upstream GPGGA message to QXWZ ntrip service, then downstream the RTCMV3 message and publish them(ie. to GPS driver node and write to physical devices)
(note that the GGA message can start with $GPGGA.... or $GNGGA...)

Things you need to obtain rtcm_v3 messages from www.qxwz.com are:

1. appkey
2. appSecret
3. deviceId
4. deviceType

The appkey and appSecret can be obtained directly from your qxwz console

![ie](https://github.com/zhangzh18/qxwz_ntrip_service_ros/blob/main/pics/2020-11-25%2019-53-52%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)

The deviceId and deviceType should be manually typied into your account via console

![ie2](https://github.com/zhangzh18/qxwz_ntrip_service_ros/blob/main/pics/2020-11-25%2019-54-50%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)

Then, modified those parameters in .roslaunch 


