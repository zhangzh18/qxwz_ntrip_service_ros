#include "qxwz_rtcm_service/qxwz_service_core.h"


ros::Publisher rtcmMsgPub;
ros::Subscriber ggaSub;
qxwz_config config;

// callback function when received a rtcmV3 msg from qxwz
void qxwz_rtcm_response_callback(qxwz_rtcm data){   

    ROS_INFO("Received rtcmV3 message");
    std::string ss(data.buffer, data.length);
    std_msgs::String msg;
    msg.data = ss;
    rtcmMsgPub.publish(msg);
}
// return code by qxwz, details can be found in qxwz_rtcm.h
void qxwz_status_response_callback(qxwz_rtcm_status code){
  	ROS_INFO("status_code = %d",code);
}

void RtcmServiceInit(std::string appkey, std::string appSecret){
    //set appKey and appSecret(get one from qxwz.com)
    config.appkey = const_cast<char*>(appkey.c_str());
    config.appSecret = const_cast<char*>(appSecret.c_str());
    config.deviceId = const_cast<char*>("sonata");
    config.deviceType= const_cast<char*>("test");

    //Set sdk configs
    qxwz_setting(&config);

    //Start rtcm sdk
    qxwz_rtcm_start(qxwz_rtcm_response_callback, qxwz_status_response_callback);
    ROS_INFO("qxwz service started");

}      

void UpdateGGA(void) {
    qxwz_rtcm_sendGGAWithGGAString(const_cast<char*>("$GPGGA,073247.50,3959.7448,N,11619.4266,E,1,10,4.1,80.65,M,-9.80,M,,*4E\r\n")); 
    ROS_INFO("send GGAMSG success");
}

void GpggaHandler(const std_msgs::StringConstPtr ggaMsg) {
    
    qxwz_rtcm_sendGGAWithGGAString(const_cast<char*>(ggaMsg->data.c_str())); 
    ROS_INFO("send GGAMSG success");
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "qxwzCore");
    ros::NodeHandle nh("~");

    std::string appkey;
    std::string appSecret;
    std::string ggaTopic;
    std::string rtcmTopic;

    nh.param<std::string>("appkey",  appkey,  std::string("--"));
    nh.param<std::string>("appSecret",  appSecret,  std::string("--"));
    nh.param<std::string>("ggaTopic",  ggaTopic,  std::string("/gpgga_topic"));
    nh.param<std::string>("rtcmTopic",  rtcmTopic,  std::string("/qxwz_rtcm_topic"));

    ROS_INFO("Starting with appkey:%s, appSecret:%s", appkey.c_str(), appSecret.c_str());
    ROS_INFO("Subscribing GPGGA message from:%s", ggaTopic.c_str());
    ROS_INFO("Transfer rtcm message with:%s", rtcmTopic.c_str());

    rtcmMsgPub = nh.advertise<std_msgs::String>(rtcmTopic, 10);
    ggaSub = nh.subscribe<std_msgs::String>(ggaTopic, 10, &GpggaHandler);
    
    RtcmServiceInit(appkey, appSecret);

    ros::Rate loop_rate(1);
    while(ros::ok()){
        UpdateGGA();
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    return 0;
}



