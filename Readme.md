# **ThePostOffice - Kernel Packet Handling Module**  

`ThePostOffice` is a Linux kernel module designed to capture incoming network packets and process them before passing them to `TheMailConditioner`. It registers a packet handler and filters out unwanted traffic before queueing packets for further processing.

The module hooks into the network stack using `dev_add_pack()`, allowing it to receive Ethernet frames directly. When a packet arrives, it checks the device name and packet type to filter out loopback and outgoing traffic. If the packet is valid, it extracts the Ethernet type to determine whether it is IPv4 or IPv6. It also identifies the transport protocol and extracts the source port. If the packet meets all conditions, it allocates a `PacketConversion` structure and queues it for processing.

The processing function finds or creates a `NetworkAdapterTable` for the incoming device. If no adapter exists, it creates one and initializes it. The adapter structure maintains a list of connected routers. The packet is then handed off to `TheMailConditionerPacketWorkHandler`, where further processing occurs.

Memory management is handled properly throughout the module. The packet buffer is freed once processing is complete using `kfree_skb()`. The dynamically allocated `PacketConversion` structure is also freed after use. When the module is unloaded, all network adapters are cleaned up to prevent memory leaks.

The module initializes itself by registering the packet handler and ensures proper cleanup when removed. It depends on `TheMailConditioner` being loaded first, as it calls an external function from that module. The build system ensures that `ThePostOffice` correctly links to `TheMailConditioner` by specifying `KBUILD_EXTRA_SYMBOLS`.

This module is designed for efficiency, using work queues to handle packets asynchronously instead of blocking the network stack. It ensures minimal overhead while processing packets in a structured manner.

## License
This project is licensed under the **Do What The F*ck You Want To Public License (WTFPL)**.  
See the [LICENSE](LICENSE) file for details.
