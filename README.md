# Hệ thống Đăng nhập và Quản lý Ví Điểm Thưởng

## 1. Giới thiệu dự án

Đây là một ứng dụng giao diện dòng lệnh (CLI) được viết bằng C++, mô phỏng hệ thống xác thực người dùng và quản lý ví điểm thưởng. Người dùng có thể đăng ký, đăng nhập, quản lý thông tin cá nhân và thực hiện các giao dịch chuyển điểm giữa các ví. Hệ thống cũng bao gồm các chức năng quản trị viên để quản lý người dùng và nạp điểm từ ví tổng. Dự án được thiết kế cho mục đích học tập nhằm thể hiện các khái niệm về quản lý người dùng, bảo mật cơ bản, xử lý giao dịch và lưu trữ dữ liệu.

## 2. Thành viên tham gia dự án

*  *Ngô Thế Quang
  
## 3. Phân tích và Đặc tả Chức năng

Hệ thống bao gồm các chức năng chính sau:

Hệ thống cung cấp các chức năng sau:

Quản lý Tài khoản Người dùng:
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

*Yêu cầu trước
*Trình biên dịch C++ (ví dụ: g++ hỗ trợ C++17).*
*Thư viện nlohmann/json (json.hpp đã có trong src/).*
*Cấu trúc Thư mục*
*src/: Các tệp mã nguồn.*
*data/: Lưu trữ users.json và wallets.json.*
*data/backups/: Lưu trữ các tệp sao lưu.*
*Hướng dẫn Biên dịch*
*Sao chép kho chứa:
*bash*

Sao chép
git clone https://github.com/<tên-người-dùng>/reward-points-system.git
cd reward-points-system
Biên dịch chương trình:
bash

Sao chép
g++ -std=c++17 src/*.cpp -o reward_points
Chạy chương trình:
bash

Sao chép
./reward_points
Cách Sử dụng
Menu Chính:
Đăng ký: Tạo tài khoản người dùng mới.
Đăng nhập: Đăng nhập bằng tên đăng nhập và mật khẩu.
Thoát: Đóng chương trình.
Menu Người dùng:
Xem Hồ sơ: Hiển thị thông tin người dùng.
Cập nhật Hồ sơ: Cập nhật họ tên, email, số điện thoại (yêu cầu OTP).
Thay đổi Mật khẩu: Cập nhật mật khẩu (bắt buộc đối với mật khẩu tự sinh).
Xem Số dư: Kiểm tra số dư ví.
Chuyển Điểm: Chuyển điểm sang ví khác (yêu cầu OTP).
Xem Lịch sử Giao dịch: Hiển thị các bản ghi giao dịch.
Menu Quản trị viên (dành cho người dùng admin):
Liệt kê Người dùng: Xem danh sách tất cả người dùng.
Tạo Người dùng: Đăng ký người dùng mới.
Nạp Điểm: Thêm điểm vào ví của người dùng từ ví tổng.
Khóa/Mở khóa Người dùng: Quản lý trạng thái tài khoản người dùng.
