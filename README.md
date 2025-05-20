# Hệ thống Đăng nhập và Quản lý Ví Điểm Thưởng

## 1. Giới thiệu dự án

Đây là một ứng dụng giao diện dòng lệnh (CLI) được viết bằng C++, mô phỏng hệ thống xác thực người dùng và quản lý ví điểm thưởng. Người dùng có thể đăng ký, đăng nhập, quản lý thông tin cá nhân và thực hiện các giao dịch chuyển điểm giữa các ví. Hệ thống cũng bao gồm các chức năng quản trị viên để quản lý người dùng và nạp điểm từ ví tổng. Dự án được thiết kế cho mục đích học tập nhằm thể hiện các khái niệm về quản lý người dùng, bảo mật cơ bản, xử lý giao dịch và lưu trữ dữ liệu.

## 2. Thành viên tham gia dự án

*  *Ngô Thế Quang
  
## 3. Phân tích và Đặc tả Chức năng

Hệ thống bao gồm các chức năng chính sau:

Hệ thống cung cấp các chức năng sau:

*Quản lý Tài khoản Người dùng:*
*Đăng ký tài khoản mới (bởi người dùng hoặc quản trị viên).
*Đăng nhập bằng tên đăng nhập và mật khẩu.*
*Thay đổi mật khẩu (bắt buộc đối với mật khẩu tự sinh trong lần đăng nhập đầu tiên).*
*Cập nhật thông tin cá nhân (họ tên, email, số điện thoại) với xác thực OTP.*
*Khóa tài khoản sau 3 lần đăng nhập thất bại.*
*Bảo mật:*
*Mật khẩu được băm với muối (salt) (phiên bản demo, không an toàn cho sản xuất).*
*OTP (Mật khẩu Một lần) cho các hành động nhạy cảm (phiên bản demo, hiển thị trên CLI).*
*Cơ chế khóa tài khoản.*
*Quản lý Ví:*
*Mỗi người dùng có một ví duy nhất liên kết với tài khoản.*
*Xem số dư ví và lịch sử giao dịch.*
*Chuyển điểm giữa các ví với xác thực OTP.*
*Quản trị viên có thể nạp điểm từ ví tổng.*
*Lưu trữ Dữ liệu:*
*Dữ liệu người dùng được lưu trong data/users.json.*
*Dữ liệu ví và giao dịch được lưu trong data/wallets.json.*
*Sao lưu tự động trong data/backups/ với dấu thời gian.*

## 4. Tải, Dịch và Cài đặt

### 4.1. Mã nguồn
Mã nguồn của dự án được tổ chức trong thư mục `src/`.

### 4.2. Cấu trúc tệp tin chính
* `src/main.cpp`: Điểm vào chính của chương trình, chứa vòng lặp menu và điều hướng chính.
* `src/UserAccount.h`, `src/UserAccount.cpp`: Định nghĩa lớp `UserAccount` quản lý thông tin người dùng.
* `src/Wallet.h`, `src/Wallet.cpp`: Định nghĩa lớp `Wallet` (ví điểm) và cấu trúc `TransactionRecord` (bản ghi giao dịch).
* `src/AuthService.h`, `src/AuthService.cpp`: Chứa logic nghiệp vụ liên quan đến xác thực, đăng ký, quản lý mật khẩu và OTP.
* `src/WalletService.h`, `src/WalletService.cpp`: Chứa logic nghiệp vụ liên quan đến quản lý ví, xem số dư, chuyển điểm.
* `src/DataStorage.h`, `src/DataStorage.cpp`: Xử lý việc đọc và ghi dữ liệu người dùng, ví từ các tệp JSON.
* `src/Utils.h`, `src/Utils.cpp`: Chứa các hàm tiện ích chung (ví dụ: tạo ID, hash mật khẩu demo, OTP demo).
* `src/Constants.h`: Định nghĩa các hằng số sử dụng trong dự án (tên tệp, ngưỡng đăng nhập sai).
* `json.hpp`: Tệp header duy nhất của thư viện nlohmann/json.
* `Makefile`: Tệp kịch bản giúp tự động hóa quá trình biên dịch.
* `data/` (thư mục được tạo tự động):
    * `users.json`: Lưu trữ danh sách tài khoản người dùng.
    * `wallets.json`: Lưu trữ danh sách các ví và lịch sử giao dịch của chúng.
