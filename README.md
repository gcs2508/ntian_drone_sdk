# Ntian SDK (support Android IOS platform)
## Mavlink ##

*	Official Website: http://mavlink.org
*	Source: [Mavlink Generator] (https://github.com/mavlink/mavlink) 
*	Binaries (always up-to-date from master):
	* [C/C++ header-only library v1](https://github.com/mavlink/c_libary_v1)
	* [C/C++ header-only library v2](https://github.com/mavlink/c_libary_v2)

### Requirements ###
	* Python 2.7+
	 * Tkinter (if GUI functionality is desired)
### Installation ###
	1. Clone into a user-writable directory.
	2. Add the repository directory to your `PYTHONPATH`
	3. Generate MAVLink parser files following the instructions in the next section *AND/OR* run included helper scripts described in the Scripts/Examples secion.
	
## Using the C implementation

Using the C implementation of MAVLink2 is very similar to using the
existing MAVLink1 implementation. You start by generating the MAVLink2
headers using mavgen.py, but passing the --wire-protocol=2.0
option. For example:

```
 mavgen.py --lang C message_definitions/v1.0/${NTIAN_MAVLINK}.xml -o ${YOURMAVPATH} --wire-protocol=2.0
```
# Android Have the Jni interface
* Android JNI interface
	* JNI_OnLoad to get the JVM
	* get ENV to call the CallBack Method function
* Methods
	* drone_connect_callback
	* normal_message_callback
	* drone_filght_mode_callback
	* drone_rssi_callback
```sequence
Android_APP-->NtianSDK: SDK_init
Android_APP-->NtianSDK:	Drone_connect 
NtianSDK-->Android_APP: Listeners NotifyConnectState
NtianSDK-->Android_APP: Listeners NotifyModeChange
NtianSDK-->Android_APP: Listeners NotifyRSSI
NtianSDK-->Android_APP: Listeners NotifyNormalMessage
Android_APP-->NtianSDK:	FollowMe GPS Location	
```
```sequence
Title: SDK init process
init_sdk-->call_back:register Call_back Methond
init_sdk-->connect_api:Get Rx or Tx apis
connect_api-->init_connect:Init connect type (serial,udp,tcp,bt,zigbee,tcp_server)
init_connect-->normal_apis:Implement Rx and Tx apis
init_connect-->init_sdk: Provide Rx and Tx methods
```
```sequence
Title: SDK connect
init_connect-->timer_handler:Create timer to send HeartBeat
timer_handler-->List_queue:push heartbeart to the List_queue,push to the Heard
init_connect-->Tx_thread:Create Tx_thread to send Messages
Tx_thread-->List_queue:Pull Message for send
Tx_thread-->normal_apis:Tx method to send Messages
init_connect-->Rx_thread:Create Rx_thread to recv Messages
Rx_thread-->normal_apis:Rx method to recv Messages
```
```sequence
Title:Rx_thread process
rx_thread-->message_parser:Mavlink messages decode
message_parser-->handler_message:Message classification
handler_message-->>call_back:Call CallBack method
call_back->drone_connect_callback:Connect States
call_back->normal_message_callback:Normal Message
call_back->drone_filght_mode_callback:Filght Mode
call_back->drone_rssi_callback:Drone Rssi 
call_back-->rx_thread:Mavlink Messages decode agin
```






















