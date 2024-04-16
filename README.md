# FLY - AND - SHOOT GAME trên AK - Embedded Base Kit

**I. Giới thiệu**

**1.1. Giới thiệu sơ lược về phần cứng.**

- AK-Embedded Base Kit [AK Embedded Base Kit - STM32L151 - Lập trình nhúng vi điều khiển (epcb.vn)](https://epcb.vn/products/ak-embedded-base-kit-lap-trinh-nhung-vi-dieu-khien-mcu) là  evaluation kit dành cho các bạn học phần mềm nhúng nâng cao và muốn thực hành với Event - Driven.
- Các ngoại vi và MCU được tính hợp vào trong Kit:
    - Vi điều khiển chính STM32 ARM-based 32-bit MCU: [STM32L151C8T6](https://www.st.com/en/microcontrollers-microprocessors/stm32l151c8.html)
    - Truyền nhận không dây 2.4Ghz RF Transceiver ICs: [NRF24L01P-R](https://www.nordicsemi.com/products/nrf24-series)
    - Giao tiếp có dây trong công nghiệp RS485 50Mbps: [THVD1450DR](https://www.ti.com/product/THVD1450/part-details/THVD1450DR)
    - Tích hợp loa dùng để làm game Buzzers Magnetic: [MLT-8530](https://www.lcsc.com/product-detail/Buzzers_Jiangsu-Huaneng-Elec-MLT-8530_C94599.html)
    - Tích hợp NOR FLASH (32MB): [W25Q256JVEIQTR](https://www.winbond.com/hq/product/code-storage-flash-memory/serial-nor-flash/index.html?__locale=en&partNo=W25Q256JV)
    - Kết nối với các mạch ứng dụng chuẩn [Seeedstudio Grove Header HY-4AW](https://wiki.seeedstudio.com/Grove_System/)
    - Tích hợp console qua USB type C sử dụng chip USB UART Converter: [CH340E](http://www.wch-ic.com/products/CH340.html)
    - Nguyên lí của phần cứng: AK-Embedded Base Kit([schematic_ak_base_kit_2.1_60965dd0f11648eab5b41cee534e0c36.pdf (hstatic.net)](https://file.hstatic.net/1000362368/file/schematic_ak_base_kit_2.1_60965dd0f11648eab5b41cee534e0c36.pdf)
- Trò chơi "Fly and Shoot" là một tựa game kinh điển đã xuất hiện từ lâu trong làng game. Đặc biệt, hiện nay trò chơi này đã được tái tạo trên nền tảng AK-Embedded Base Kit, với việc tích hợp một hệ thống quản lý nhiệm vụ, tín hiệu, bộ đếm thời gian, và tin nhắn kết hợp với một cơ chế Event-Driven.
- Bằng cách sử dụng cơ chế Event-Driven, trò chơi có thể phản ứng linh hoạt theo sự kiện diễn ra trong trò chơi một cách tự nhiên, tạo ra trải nghiệm chơi game mượt mà và hấp dẫn hơn cho người chơi. Điều này giúp tăng cường sự tương tác và động lực cho người chơi trong quá trình tham gia vào trò chơi "Fly and Shoot".

**1.2. Màn hình Menu**

- PLAY: Bắt đầu trò chơi.
- SETTING: Cài đặt cái thông số cho trò chơi mode(chế độ), missile(đạn), âm thanh(bật/tắt).
- TUTORIAL: QR hướng dẫn trò chơi.
- HISTORY: Lưu lịch trò điểm sau những lần chơi.
- EXIT: Thoát màn hình menu.

**1.3. Các đối tương hoạt động trong game.**

| Đối tượng | Ý nghĩa | Người chơi tác động | Tự động tác động |
| --- | --- | --- | --- |
| PLANE | Tàu bay | Di chuyển tàu bay đi lên  | Di chuyển tàu bay đi xuống, chạm quặng, bom sẽ tạo ra vụ nổ và kết thúc game |
| MISSILE | Đạn | Bắn ra đạn phá hủy quặng, bom | Di chuyển, tạo ra vụ nổ khi chạm quặng, bom, tạo ra điểm khi chạm quặng |
| MINE | Quặng | Không | Di chuyển, tự động tạo ra |
| BOM | Bom | Không | Di chuyển, tự động tạo ra |
| EXPLOSION | Vụ Nổ | Không | Vụ nổ xảy ra khi đạn chạm quặng hoặc bom |
| MAP | bản đồ | Không | Di chuyển bản đồ |

**1.4. Cách chơi của game.**

Người chơi có thể điều khiển tàu đi lên (UP) hoặc để tàu bay tự động rơi xuống để né các quặng và bom không chạm vào máy bay. Đồng thời cũng không được để tàu bày chạm vào đường hầm (MAP). 

Tăng độ khó bằng cách vào cài đặt và chỉnh mode (EASY, NORMAL, HARD).

Có thể bắn đạn bằng cách nhấn nút MODE khi đạn chạm trúng các quặng sẽ tạo ra điểm. Số đạn có thể tùy chỉnh được trong SETTING và được giới hạn tối đa là 5 viên.

*Cách tính điểm:*

- Quặng nhỏ sẽ có 1 điểm khi bắn trúng.
- Quặng lớn sẽ có 2 điểm khi bắn trúng.
- Bom sẽ không có điểm khi bắn trúng.

Số điểm sẽ được lưu khi trò chơi kết thúc. Khi trò chơi kết thúc nhấn MODE để chơi tiếp, nhấn DOWN để quay trở về menu.

**II. Thiết kế các Task, Signal trong game.**

**2.1. Event - Driven hoạt động như thế nào ?**

![Untitled](FLY%20-%20AND%20-%20SHOOT%20GAME%20tre%CC%82n%20AK%20-%20Embedded%20Base%20Ki%202c299bf52b084d58b18f0795a20bb07c/Untitled.png)

                                             *Nguồn: Automatic Control Programming*

- Event Driven nói một cách dễ hiểu là một hệ thống gửi thư (gửi message) để thực thi các công việc. Trong đó, Task đóng vai trò là người nhận thư, Signal đại diện cho nội dung công việc. Task & Signal nền tảng của một hệ Event Driven.
- Thông thường mỗi Task sẽ nhận một nhóm công công việc nào nào đó, ví dụ: quản lý state-machine, quản lý hiển thị của màn hình, quản lý việc cập nhật phần mềm, quản lý hệ thống watchdog ...
- Message được chia làm 2 loại chính, Message chỉ chứa Signal, hoặc vừa chứa Signal và Data. Message tương đương với Signal.
- Chỗ thực thi một công việc nào đó thì mình gọi là Handler.

Chi tiết các khái niệm các bạn tham khảo tại bài viết: [AK Embedded Base Kit - STM32L151 - Event Driven: Task & Signal](https://epcb.vn/blogs/ak-embedded-software/ak-embedded-base-kit-stm32l151-event-driven-task-signal)  

**2.2. Task và Signal trong Fly - And - Shoot.**

*Các Task và Priority trong game:*

| TASK | PRIORITY | HANDLER |
| --- | --- | --- |
| AC_TASK_DISPLAY_GAME_ON_ID | TASK_PRI_LEVEL_4	 | task_scr_game_on_handle |
| AC_TASK_PLANE_ID | TASK_PRI_LEVEL_4	 | task_prc_plane_hanle		 |
| AC_TASK_MISSILE_ID			 | TASK_PRI_LEVEL_4	 | task_prc_missile_handle		 |
| AC_TASK_WALL_ID			 | TASK_PRI_LEVEL_3 | task_prc_wall_handle		 |
| AC_TASK_EXPLOSION_ID | TASK_PRI_LEVEL_4	 | task_prc_explosion_handle	 |
| AC_TASK_BOM_ID				 | TASK_PRI_LEVEL_3 | task_prc_bom_handle			 |
| AC_TASK_MINE_ID			 | TASK_PRI_LEVEL_3 | task_prc_mine_handle		 |
| AC_TASK_DISPLAY_GAME_OVER_ID | TASK_PRI_LEVEL_4	 | task_scr_game_over_handle	 |

                            **

*Sơ đồ quá trình trước khi và sau khi vào game:*

![Untitled](FLY%20-%20AND%20-%20SHOOT%20GAME%20tre%CC%82n%20AK%20-%20Embedded%20Base%20Ki%202c299bf52b084d58b18f0795a20bb07c/Untitled%201.png)

                           *Hình 1 : Sơ đồ quá trình trước khi bắt đầu vào game*

Giải thích :

| SCREEN_ENTRY | Khi người dùng bắt đầu chơi game |
| --- | --- |
| SIG_DISPLAY_GAME_ON_TICK | Signal do timer gửi đến với chu kì 100ms cập nhật lại màn hình |
| SIG_PLANE_SETUP | Cài đặt thông số mặc định cho tàu bay |
| SIG_PLANE_ON_TICK | Signal do timer gửi đến với chu kì 100ms giúp tàu bay đi xuống |
| SIG_MINE_RESET | Cài đặt thông số mặc định cho quặng |
| SIG_MINE_ON_TICK | Signal do timer gửi đến với chu kì 150ms dùng để di chuyển quặng |
| SIG_MINE_PUSH | Signal do timer gửi đến với chu kì 1500ms dùng để tạo thêm quặng |
| SIG_BOM_RESET | Cài đặt lại tất cả các thông số bom |
| SIG_BOM_ON_TICK | Signal do timer gửi đến với chu kì 150ms dùng để di chuyển bom |
| SIG_BOM_PUSH | Signal do timer gửi đến với chu kì 1800ms dùng để tạo thêm bom |
| SIG_MISSILE_RESET | Cài đặt lại tất cả các thông số cho đạn |
| SIG_WALL_RESET | Cài đặt lại tất cả các thông số cho hầm |
| SIG_WALL_ON_TICK | Signal do timer gửi đến với chu kì 100ms dùng để di chuyển hầm |
| SIG_EXPLOSION_RESET | Cài đặt lại tất cả các thông số cho vụ nổ |
| SIG_EXPLOSION_ON_TICK | Signal do timer gửi đến với chu kì 150ms dùng để tạo hoạt ảnh cho vụ nổ |
| state_game | Biến lưu trạng thái của game |

![Untitled](FLY%20-%20AND%20-%20SHOOT%20GAME%20tre%CC%82n%20AK%20-%20Embedded%20Base%20Ki%202c299bf52b084d58b18f0795a20bb07c/Untitled%202.png)

                              *Hình 2 : Sơ đồ quá trình khi game đang chạy*

Giải thích :

| SIG_DISPLAY_GAME_ON_TICK | Signal do timer gửi đến với chu kì 100ms  |
| --- | --- |
| SIG_PLANE_CRASH | Signal kiểm tra tàu bay có chạm vào bom, quặng hay tường  |
| SIG_DISPLAY_GAME_OVER_ON_TICK | Signal tạo ra khoảng chờ để chuyển đến màn hình game over |
| SIG_MISSILE_ON_TICK | Signal do timer gửi đến với chu kì 100ms dùng để di chuyển bom |
| SIG_MISSILE_CRASH | Signal kiểm tra đạn có chạm vào bom hay quặng  |
| RELOAD SCREEN | Giúp cập nhật lại toàn bộ màn hình |

![Untitled](FLY%20-%20AND%20-%20SHOOT%20GAME%20tre%CC%82n%20AK%20-%20Embedded%20Base%20Ki%202c299bf52b084d58b18f0795a20bb07c/Untitled%203.png)

                         *Hình 3 : Sơ đồ người dùng tác động vào khi game đang chạy*

Giải thích :

| SIG_PLANE_UP | Player nhấn [Up] tạo ra signal giúp tàu bay đi lên |
| --- | --- |
| SIG_MISSILE_PUSH | Player nhấn [Mode] tạo ra signal giúp bắn ra đạn |

                                                      **

![Untitled](FLY%20-%20AND%20-%20SHOOT%20GAME%20tre%CC%82n%20AK%20-%20Embedded%20Base%20Ki%202c299bf52b084d58b18f0795a20bb07c/Untitled%204.png)

                                                      *Hình 4: Sơ đồ khi game over*