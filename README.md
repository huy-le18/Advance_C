# ADVANCE C/C++ ALGORITHM (HalaAcademy)

## BÀI 1: COMPILER VÀ CÁC CHỈ THỊ TIỀN XỬ LÝ

### 1. QUÁ TRÌNH BIÊN DỊCH (COMPILER)

**Compiler** là một quá trình máy tính chuyển đổi mã nguồn được viết bằng một ngôn ngữ lập trình (như C, C++,...) thành mã máy (machine code) mà máy tính có thể hiểu và thực thi.

**BAO GỒM 4 BƯỚC:**
![anh1](compiler.png)
#### Bước 1: Tiền xử lý (Preprocessing)
+ Copy tất cả nội dung trong các file được #include
+ Thay thế các Macro # 
+ Lược bỏ chú thích  //, /**/
Sau quá trình này file `source.c -> source.i`
Ta có 2 file `main.c` và `hello.c`
![anh1](File2C.png) 

Sau khi thực hiện lệnh `gcc -E hello.c -o hello.i` và `gcc -E main.c -o main.i`
Ta đc 2 file `main.i` và `hello.i`
 ![anh1](file2I.png) 


#### Bước 2: Compilation
+ Trình biên dịch chuyển mã nguồn thành mã assembly.
Sau quá trình này file `source.i -> source.s`

Thực hiện lệnh `gcc -S main.i -o main.s` và `gcc -S hello.i -o hello.s`
 ![anh1](file2S.png) 

#### Bước 3: Assemble
+ Trình biên dịch chuyển từ mã máy thành mã nhị phân.
Sau quá trình này file `source.s -> source.o`

Thực hiện lệnh `gcc -c main.s -o main.o` và `gcc -c hello.s -o hello.o`
 ![anh1](file2O.png) 

#### Bước 4: Linking
+ Liên kết các module và các thư viện liên kết thành file thực thi.
+ Hợp các file nguồn, file thư viện thành 1 file thực thi duy nhất `source.exe`
  
Thực hiện lệnh `gcc main.o hello.o -o main` để hợp nhất thành 1 file thực thi `main.exe` 
 ![anh1](fileEXE.png) 
+ Chạy file thực thi 

        PS C:\Users\Huy Le\Documents\HALAacedemy\Code\CodeC_Advance\B1> gcc main.o hello.o -o main
        PS C:\Users\Huy Le\Documents\HALAacedemy\Code\CodeC_Advance\B1> ./main
        hello everyone
        function 1


### 2. CÁC CHỈ THỊ TIỀN XỬ LÝ

#### - Chỉ thị bao hàm tệp (#include)
Chỉ thị `#include` cho phép gộp file khác vào file chúng ta đang viết
ví dụ:
![anh1](include.png) 

Sau quá trình tiền xử lý:
![anh1](include2.png) 

Ta có thể thấy toàn bộ nội dung file `hello.h` đã được copy vào `main.c`
#### - Chỉ thị định nghĩa cho tên (#define macro)  

**Marco** là một cách để định nghĩa lại một giá trị hay một chuỗi các lệnh nhằm tránh lặp lại mã và có thể làm cho chương trình dễ bảo trì hơn. 
**Marco** được định nghĩa bằng chỉ thị `#define` 

`#define PI 3.14`   
`#define MAX(a, b) ((a) > (b) ? (a) : (b))`     

**Variadic Macro** (macro biến số) là loại macro trong C có thể nhận một số lượng tham số không xác định. Chúng cho phép định nghĩa các macro có thể xử lý nhiều tham số hơn so với macro thông thường.
Cú pháp: 
#define DISPLAY(...)   ____VA_ARGS____
Trong đó:
+ `...`: Đại diện cho các tham số biến đổi
+ __VA_ARGS__: Đại diện cho các tham số biến đổi trong phần thân của macro.

Ví dụ:
Bài toán tính tổng của 1 dãy số:

Ở file main.c

    #include "stdio.h"
    #define tong(...)  \
    int array[] = {__VA_ARGS__, -1};\         // __VA_ARGS__ = ...
    int i = 0;                      \
    int sum = 0;                    \
    while(array[i] != -1)           \
    {                               \
        sum = sum + array[i];       \
        i ++;                       \
    }                               \
    printf("tong = %d\n", sum);


    int main()
    {
        tong(4,5,7,9,11);                   // __VA_ARGS__ = 4,5,7,9,11
        
        return 0;
    }


Ở file main.i

    int main()
    {
        int array[] = {4,5,7,9,11, -1};      // __VA_ARGS__ đã được thay vào 
        int i = 0;
        int sum = 0;
        while(array[i] != -1)
        { 
        sum = sum + array[i]; 
        i ++; 
        } 
        printf("tong = %d\n", sum);;

        return 0;
    }

Một số ứng dụng của **Variadic Macro**: 

+ **Log messages**: Viết các macro để ghi lại thông báo log với định dạng tùy ý.
`#define LOG(format, ...) fprintf(stderr, format, __VA_ARGS__)`
+ **Debugging**: Thêm thông tin như tên hàm, file nguồn, hoặc dòng số vào thông báo debug.
`#define DEBUG(format, ...) fprintf(stderr, "[DEBUG] %s:%d: " format, __FILE__, __LINE__, __VA_ARGS__)`
## BÀI 2: STDARG - ASSERT
### 1.Thư viện #include <stdarg.h> 
Variadic functions (hàm biến số tham số) là các hàm trong C có thể nhận một số lượng tham số không xác định. Điều này khác với các hàm thông thường, nơi số lượng tham số được xác định tại thời điểm khai báo hàm
Cách sử dụng:
+ Khai báo hàm: `int sum(int count, ...)` cho phép hàm nhận một số lượng tham số biến đổi sau tham số cố định count.
+ Macro `va_list`: Được sử dụng để khai báo một biến có thể truy cập các tham số nhập vào.
+ Macro `va_start`: Được sử dụng để khởi tạo danh sách các tham số biến đổi. Nó nhận vào hai tham số: danh sách args và tên của label làm mốc. Ví dụ ở đây là label `count`
+ Macro `va_arg`: Được sử dụng để truy xuất từng tham số biến đổi từ danh sách args. Mỗi lần gọi va_arg, bạn nhận được giá trị của tham số tiếp theo với kiểu dữ liệu được chỉ định ví dụ ở đây là `int`.
+ Macro `va_end`: Được sử dụng để kết thúc việc truy cập danh sách các tham số biến đổi.

Một số ứng dụng của **Variadic Function**: 
**Tạo các hàm xử lý nhiều tham số** 


Bài tập: tính tổng của 1 dãy số.

    #define tong(...)   sum(__VA_ARGS__, 0)    /*giá trị 0 là dấu hiệu kết thúc*/
    int sum(int count,...) 
    {
        va_list va;      /*khai báo 1 biến để truy cập tham số nhập vào*/
        int sum = count; 

        va_start(va, count);   /*khởi tạo danh sách tham số bắt đầu từ label count*/
        int value;

        while ((value = va_arg(va, int)) != 0)  /*lấy giá trị và kiểm tra */
        {
            sum += value;
        }

        va_end(va);                            /*kết thúc*/

        return sum;
        
    }

    int main()
    {
        printf("Tong: %d\n", tong(6, 1,4, 5,9,6,4));

        return 0;
    }

Kết quả: 
`Tong: 35`

+**Xây dựng hàm để xử lý dữ liệu** 

Bài tập: viết hàm xử lý 2 hay nhiều cảm biến:

    #include <stdio.h>
    #include <stdarg.h>

    typedef enum{
        TEMPERATURE_SENSOR,
        PRESSURE_SENSOR
    }SensorType;

    void processSensorData(SensorType type, ...)
    {
        va_list args;               /*khai báo 1 biến để truy cập tham số nhập vào*/
        va_start(args, type);      // xác định lable để lấy dữ liệu 
        switch (type)
        {
            case TEMPERATURE_SENSOR:
            {
                int numArgs = va_arg(args, int);            // lấy dữ liệu 1 ép kiểu int 
                int sensorId = va_arg(args, int);           // lấy dữ liệu 2 ép kiểu int
                float temperature = va_arg(args, double);   // lấy dữ liệu 3 ép kiểu double 

                
                printf("Temperature Sensor ID: %d, Reading: %.2f degrees\n", sensorId, temperature);
                if(numArgs > 2)
                {
                    // xử lí thêm tham số nếu có 
                    char* additionalInfo = va_arg(args, char*);  // lấy dữ liệu 4 ép kiểu char* 
                    printf("Additional Info:%s\n", additionalInfo); 
                }
                break;
            }
            case PRESSURE_SENSOR: 
            {
                int numArgs = va_arg(args, int);
                int sensorId = va_arg(args, int);
                int pressure = va_arg(args, int);
                printf("Pressure Sensor ID: %d, Reading: %d Pa\n", sensorId, pressure);
                if(numArgs > 2)
                {
                    // Xử lý thêm tham số nếu có
                    char* unit = va_arg(args, char*);
                    printf("Unit: %s\n", unit);
                }
                break;
            }     

            default:
                break;
        }

        va_end(args);                
    }


    int main()
    {
        processSensorData(TEMPERATURE_SENSOR, 3, 1, 36.5, "Room Temperature");
        processSensorData(PRESSURE_SENSOR, 3, 2, 101325);    
        return 0;
    }
Kết quả:

    Temperature Sensor ID: 1, Reading: 36.50 degrees
    Additional Info:Room Temperature
    Pressure Sensor ID: 2, Reading: 101325 Pa
    Unit: Room Temperature

## BÀI 3: CON TRỎ (POINTER)

### 1. Con trỏ
**Con trỏ** là một biến mà trong đó giá trị của nó là địa chỉ của một biến khác.
**Cách sử dụng con trỏ:**
- *Khai báo con trỏ*: `type *pointer_name;`
- *Gán địa chỉ cho con trỏ*: sử dụng toán tử `&` ví dụ:
    `int a = 10;`
    `int *ptr = &a;  // khai báo và gán giá trị địa chỉ biến a cho con trỏ ptr`
- *Truy cập giá trị thông qua con trỏ*: sử dụng toán tử `*` ví dụ: 
    `*ptr = 20 // thay đổi giá trị của địa chỉ mà ptr đang trỏ tới = 20`    

Ví dụ: 

    int a = 10;
    int *ptr = &a;  // khai báo và gán giá trị địa chỉ biến a cho con trỏ ptr

    printf("dia chi cua bien a: %p\n", &a);             // in ra địa chỉ biến a
    printf("gia tri cua con tro ptr: %p\n", ptr);       // in ra giá trị của ptr

    printf("gia tri cua bien a: %d\n", a);              // in ra giá trị của biến a
    printf("gia tri tai dia chi ptr tro den: %d\n", *ptr);     // in ra giá trị tại địa chỉ ptr trở đến
Kết quả in ra Terminal: 

    dia chi cua bien a:      000000048FFFFDD4
    gia tri cua con tro ptr: 000000048FFFFDD4
    gia tri cua bien a: 10
    gia tri tai dia chi ptr tro den: 10

**Con trỏ void**:
+ Là 1 con trỏ có thể trỏ đến bất kì kiểu dữ liệu nào. 
+ Phải thực hiện ép kiểu con trỏ `void` trước khi truy suất giá trị. Do con trỏ `void` không có kiểu dữ liệu cụ thể nên trình biên dịch không biết cần đọc bao nhiêu byte.


ví dụ:

    #include "stdio.h"

    int main()
    {
        int a = 10;
        void *p = NULL;                  // khai báo con trỏ NULL
        p = &a;                          // gán địa chỉ biến a cho p;
        printf("*p = %d \n", *(int*)p);  // ép thành kiểu int* để truy suất giá trị

        return 0;
    }

Kết quả:

    *p = 10 

**Hằng con trỏ (Pointer to Constant)**: 
`Pointer to Constant` là được sử dụng khi thiết kế các hàm cho phép người dùng chỉ đọc chứ không được phép ghi. 
+ Cú pháp: `const type *pointer_name;`  Ví dụ: `const char *str1`
+ Không thể thay đổi giá trị tại địa chỉ mà con trỏ trỏ tới.
+ Có thể thay đổi đại chỉ mà con trỏ trỏ tới.
Ví dụ: 
Bài toán sắp xếp sinh viên. 
Có 1 số các hàm tạo ra chỉ để đọc dữ liệu và xử lí. Ta sử dụng const để ngăn chặn việc thay đổi giá trị. 

        int stringCompare(const char *str1, const char * str2)  // khai báo kiểu const
        {
            while (*str1 && (*str1 == *str2))           // đọc giá trị 
            {
                str1 ++;
                str2 ++;
            }
            /*đọc giá trị*/
            return *(const unsigned char*) str1 - *(const unsigned char*) str2;
        }
        /*Truyền vào hàm */
        int compareByName(const void *a, const void *b)
        {
            /*Ép về kiểu SinhVien để truy suất giá trị*/
            SinhVien *sv1 = (SinhVien *)a;
            SinhVien *sv2 = (SinhVien *)b;

            /*Đọc giá trị*/
            return stringCompare(sv1 -> ten, sv2 -> ten);
        }
        
        int compareByDiemTrungBinh(const void *a, const void *b)
        {
            /*Ép về kiểu SinhVien để truy suất giá trị*/
            SinhVien *sv1 = (SinhVien *)a;
            SinhVien *sv2 = (SinhVien *)b;

            /*Đọc giá trị*/
            if(sv1 -> diemTrungBinh > sv2->diemTrungBinh)
            {
                return 1;
            }
            return 0;
        }

**Con trỏ hằng (Constant Pointer)**: 
`Con trỏ hằng (constant pointer)` là một con trỏ mà giá trị của chính con trỏ đó (tức là địa chỉ mà nó trỏ tới) không thể thay đổi sau khi được khởi tạo. Nói cách khác, một khi đã gán một địa chỉ cụ thể cho con trỏ hằng, thì không thể làm cho nó trỏ tới một địa chỉ khác. Tuy nhiên, vẫn có thể thay đổi giá trị tại địa chỉ mà con trỏ hằng trỏ tới.
+ Cú pháp: `type *const pointer_name;`  Ví dụ: `char *const str1`

Ứng dụng:

Trong lập trình vi điều khiển. Để đảm bảo rằng các con trỏ truy cập các thanh ghi này không bị thay đổi địa chỉ trong quá trình thực thi, con trỏ hằng có thể được sử dụng.

`unsigned int * const PORTA = (unsigned int *)0x40004000;`

Giá trị của con trỏ PORTA được gán = `0x40004000`

Một ví dụ khác về con trỏ hằng:

    #include <stdio.h>

    int main() {
        int x = 10;
        int *const ptr = &x;  // Con trỏ hằng trỏ đến x

        *ptr = 20;  // Hợp lệ: thay đổi giá trị của x thông qua con trỏ hằng
        printf("x = %d\n", x);  // In ra 20

        int y = 30;
        // ptr = &y;  // Lỗi: không thể thay đổi địa chỉ mà con trỏ hằng trỏ tới

        return 0;
    }

### 2. Con trỏ hàm
**Con trỏ hàm** được dùng để lưu trữ địa chỉ của một hàm. Điều này cho phép gọi hàm thông qua con trỏ, điều này hữu ích trong các trường hợp như truyền hàm làm đối số cho các hàm khác. 
**Cách sử dụng con trỏ hàm:**
- *Khai báo con trỏ hàm*: `return_type (*pointer_name)(parameter_types);`
  ví dụ: `int (*pFunc)(int, int);`
- Gán địa chỉ hàm cho con trỏ:
  
  ví dụ: 

        int add(int a, int b) 
        {
            return a + b;
        }
        pFunc = add;
- Gọi hàm thông qua con trỏ:
    `int result = pFunc(5, 3); // Kết quả là 8`

ví dụ:

    #include <stdio.h>
    int add(int a, int b)
    {
        return a + b;
    }

    int main()
    {
        int (*ptr)(int,int);

        ptr = add;
        int sum = ptr(3,5);
        printf("sum = %d\n", sum);     // in ra giá trị tại địa chỉ ptr trở đến

        return 0;
    }

Kết quả:
 `sum = 8`

Ứng dụng của con trỏ hàm:
Trong bài toán tổng, hiệu, thương, tích:

    #include "stdio.h"
    #include <assert.h>

    void tong(int a, int b)
    {
        printf("Tong %d va %d: %d\n", a, b, a + b);
    }

    void hieu(int a, int b)
    {
        printf("Hieu %d va %d: %d\n", a, b, a - b);
    }

    void tich(int a, int b)
    {
        printf("Tich %d va %d: %d\n", a, b, a * b);
    }

    void thuong(int a, int b)
    {
        assert(b != 0);
        printf("Thuong %d va %d: %d\n", a, b, a / b);
    }

    /* Viết 1 hàm tính toán chung*/
    /* Với các tham số truyền vào
    + void (*ptr) (int, int): Địa chỉ của hàm thực hiện
    + int a: số hạng thứ nhất
    + int b: số hạng thứ hai
     */
    void tinhToan (void (*ptr) (int, int), int a, int b)
    {
        printf("Thuc hien phep toan duoi:\n");
        /* sử dụng con trỏ hàm để gọi tới các hàm tương ứng */
        ptr(a,b);
    }

    int main()
    {
        tinhToan(&tong, 4, 5);
        tinhToan(&hieu, 7, 5);
        tinhToan(&tich, 4, 5);
        tinhToan(&thuong, 10, 5);
        return 0;
    }

Kết quả:

    Thuc hien phep toan duoi:
    Tong 4 va 5: 9
    Thuc hien phep toan duoi:
    Hieu 7 va 5: 2
    Thuc hien phep toan duoi:
    Tich 4 va 5: 20
    Thuc hien phep toan duoi:
    Thuong 10 va 5: 2

## BÀI 4: Extern - Static - Volatile - Register
### 1. Extern

Trong ngôn ngữ lập trình C, từ khóa `extern` được sử dụng để khai báo một biến hoặc hàm đã được định nghĩa ở nơi khác, có thể là trong một file khác hoặc ở một vị trí khác trong cùng file. Từ khóa này được dùng để thông báo cho trình biên dịch rằng biến hoặc hàm này tồn tại, nhưng nó sẽ không được định nghĩa tại vị trí này.

Ví dụ:

![anh1](extern2.png) 

Kết quả in ra terminal: 



Ở file `test.c` ta có 1 biến `count` và 1 hàm void `prinf_count(void)`

Ở file `main.c` không cần #include file mà chỉ cần dùng từ khóa `extern`. Sau đó ta có thể sử dụng chúng.

    Value of count: 10
    Valua of count: 50

### 2. Static
#### Biến static cục bộ
Thông thường, các biến cục bộ chỉ tồn tại trong thời gian hàm được gọi và sẽ bị hủy sau khi hàm kết thúc. Tuy nhiên, `biến static cục bộ` vẫn tồn tại trong suốt thời gian chương trình chạy.
**Đặc điểm**:
+ Chỉ khởi tạo 1 lần duy nhất. Lần thứ 2 gọi sẽ không khởi tạo lại.
+ Tồn tại hết vòng đời chương trình.
+ Chỉ có giá trị trong hàm.
  
**Ứng dụng**:
+ Khởi tạo các giá trị ban đầu
+ Dùng để lưu giá trị (thời gian,...) giữa 2 lần gọi hàm. Ví dụ hàm `millis()` trong Arduino.  

Ví dụ:

    #include <stdio.h>

    void func() {
        static int count = 0; // Biến count là static
        count++;
        printf("Count = %d\n", count);
    }

    int main() {
        func();
        func();
        func();
        return 0;
    }

Kết quả: 

    Count = 1
    Count = 2
    Count = 3

#### Biến static toàn cục và hàm static
**Biến static toàn cục**
Khi một biến static được khai báo toàn cục, biến đó chỉ có thể được truy cập trong file mà nó được định nghĩa. Điều này nghĩa là phạm vi truy cập của biến toàn cục static bị giới hạn trong phạm vi của file, giúp ngăn chặn việc truy cập ngoài ý muốn từ các file khác. 

Ví dụ:
![anh1](static.png) 

Kết quả trên terminal báo chưa khai báo: 

    main.o:main.c:(.rdata$.refptr.count[.refptr.count]+0x0): undefined reference to `count'

Giải thích: 
Ở file `test.c` ta có khai báo biến `static int count = 10;` 
Ở file `main.c` ta dùng từ khóa `extern int count` để sử dụng biến này ở file `main.c`
Kết quả trình biên dịch báo lỗi `undefined reference to 'count'`

**Hàm Static**

Khi một hàm được khai báo với từ khóa `static`, hàm đó chỉ có thể được gọi từ bên trong file mà nó được định nghĩa, tương tự như biến toàn cục static. Điều này giúp hạn chế phạm vi truy cập của hàm, tránh xung đột tên hàm với các file khác.

Ứng dụng:
+ Khi người dùng sử dụng hàm lớn (được xây dựng từ các hàm nhỏ). Ta cần khai báo thêm từ khóa `static` ở các hàm nhỏ để tránh xung đột.  

Ví dụ bài toán tìm nghiệm phương trình bậc 2:

Trong file `solve.c`

    #include <stdio.h>
    #include <math.h>

    // Hàm static để tính delta
    static double calculateDelta(double a, double b, double c) {
        return b * b - 4 * a * c;
    }

    // Hàm public để tìm nghiệm dựa trên delta
    void findRoots(double a, double b, double c) {
        double delta = calculateDelta(a, b, c); // Tính delta
        double x1, x2;

        if (delta > 0) {
            x1 = (-b + sqrt(delta)) / (2 * a);
            x2 = (-b - sqrt(delta)) / (2 * a);
            printf("Phương trình có hai nghiệm phân biệt: x1 = %.2lf và x2 = %.2lf\n", x1, x2);
        } else if (delta == 0) {
            x1 = -b / (2 * a);
            printf("Phương trình có nghiệm kép: x1 = x2 = %.2lf\n", x1);
        } else {
            printf("Phương trình vô nghiệm\n");
        }
    }

Trong file `main.c` 

    #include <stdio.h>

    // extern hàm findRoots từ solve.c
    extern void findRoots(double a, double b, double c);

    int main() {
        double a, b, c;

        // Nhập hệ số a, b, c từ người dùng
        printf("Nhập hệ số a (a ≠ 0): ");
        scanf("%lf", &a);
        printf("Nhập hệ số b: ");
        scanf("%lf", &b);
        printf("Nhập hệ số c: ");
        scanf("%lf", &c);

        // Gọi hàm findRoots để giải phương trình
        findRoots(a, b, c);

        return 0;
    }


Giải thích: Trong file `solve.c` hàm `static double calculateDelta(double a, double b, double c)` được khai báo để tính delta sử dụng cho hàm `void findRoots(double a, double b, double c)`.

### 3. Register

`Register` được sử dụng để yêu cầu trình biên dịch lưu trữ một biến cụ thể trong một thanh ghi của CPU thay vì trong bộ nhớ RAM thông thường. Điều này có thể giúp tăng tốc độ truy xuất biến vì thanh ghi của CPU có tốc độ truy cập nhanh hơn nhiều so với bộ nhớ. Biến `Register` chỉ được khai báo cục bộ, không thể khai báo là biến toàn cục. 
Quá trình hoạt động của ALU: 
![anh1](ALU2.png) 

Ưu điểm khi dùng `Register`:
+ Tốc độ: nhanh hơn do không mất thời gian truy cập từ RAM về thanh ghi và từ thanh ghi về RAM. 

Nhược điểm khi dùng `Register`:

+ Giới hạn thanh ghi: CPU chỉ có một số lượng thanh ghi giới hạn.

+ Không thể lấy địa chỉ của biến `Register`: Vì biến `Register` có thể không có địa chỉ cố định trong bộ nhớ nên không thể sử dụng toán tử & để lấy địa chỉ của biến `Register`.

Ví dụ: 
Kiểm tra tốc độ chương trình khi dùng `Registor`.

Chương trình khi không dùng register:

    #include <stdio.h>
    #include <time.h>

    int main(int argc, char const *argv[])
    {
        unsigned long i;
        clock_t start, end;
        start = clock();
        for( i = 0; i < 99999999; i ++);
        end = clock();
        printf("run time without registor: %f\n", (double)(end - start)/1000);
    }

Kết quả: 

    run time without registor: 0.287000

Chương trình khi dùng register:

    #include <stdio.h>
    #include <time.h>

    int main(int argc, char const *argv[])
    {
        register unsigned long i;
        clock_t start, end;
        start = clock();
        for( i = 0; i < 99999999; i ++);
        end = clock();
        printf("run time with registor: %f\n", (double)(end - start)/1000);
    }
Kết quả:

    run time with registor: 0.096000

### 4. Volatile

Từ khóa `volatile` được sử dụng để thông báo cho trình biên dịch biết không được tối ưu biến đó.
Khi nào xử dụng `volatile`:
**Truy cập vào phần cứng**: Khi làm việc với các thanh ghi phần cứng hoặc các thiết bị ngoại vi, giá trị của biến có thể thay đổi khi phần cứng cập nhật, ngay cả khi không có lệnh nào trong chương trình thay đổi giá trị đó.
**Biến được chia sẻ giữa các luồng (threads)**: Khi làm việc với lập trình đa luồng, một biến có thể được thay đổi bởi một luồng khác. Từ khóa `volatile` đảm bảo rằng mỗi lần biến được đọc, giá trị mới nhất của nó được truy xuất từ bộ nhớ chứ không phải từ bộ nhớ đệm của một luồng.
**Xử lý tín hiệu (Signal Handlers)**:Trong các chương trình xử lý tín hiệu, một biến có thể được thay đổi trong một trình xử lý tín hiệu bất kỳ thời điểm nào. Từ khóa volatile giúp đảm bảo rằng các biến này được xử lý chính xác.

Ví dụ:

    #include <stdio.h>
    #include <stdbool.h>

    // Giả sử đây là một biến điều khiển phần cứng
    volatile int hardware_status = 0;

    int main() {
        while (hardware_status == 0) {
            // Đợi phần cứng thay đổi giá trị của hardware_status
        }
        printf("Hardware status đã thay đổi!\n");
        return 0;
    }


Giải thích:

+ Trong ví dụ này, `hardware_status` là một biến có thể thay đổi bởi phần cứng. Nếu không sử dụng `volatile`, trình biên dịch có thể tối ưu hóa vòng lặp while, bằng cách đọc giá trị của `hardware_status` một lần và giả định rằng nó sẽ không thay đổi trong suốt vòng lặp. Điều này dẫn đến một vòng lặp vô hạn vì giá trị không được kiểm tra lại từ bộ nhớ.
+ Khi sử dụng `volatile`, trình biên dịch sẽ không tối ưu hóa việc đọc biến, và sẽ kiểm tra lại giá trị của `hardware_status` trong mỗi vòng lặp.

## BÀI 5: Goto-Setjump
### 5.1. Goto
`Goto` là 1 từ khóa trong lập trình C, cho phép chương trình nhảy đến một nhãn(label) đã được đặt trước đó trong cùng 1 hàm. 
**Cú pháp:**

    goto label_name;
    // các lệnh khác
    label_name: 
    // các lệnh sau khi nhảy đến nhãn

Ví dụ:

Cho 1 chương trình khởi tạo 1 biến `num = 0` nếu số đó nhỏ hơn 10 thì quay lại nhãn `label_begin:`
để cộng số đó thêm 1 đơn vị. Nếu lớn hơn hoặc bằng 10 thì nhảy đến `label_end` để kết thúc chương trình. 

    #include <stdio.h>

    int main() {
        int num = 0;

        label_begin:
        printf("Jumped to label begin.\n");
        num ++;

        if (num < 10) {
            printf("num: %d\n", num);
            // nếu nhỏ hơn thì quay lại label_begin.
            goto label_begin;
        }
        else{

            printf("\n");
            // nếu lớn hơn hoặc bằng thì nhảy đến label_end.
            goto label_end;
        }

        printf(" Phần này không được in ra.\n");


        label_end:
        printf("Jumped to label end.\n");

        return 0;
    }


Kết quả: 

    Jumped to label begin.
    num: 1
    Jumped to label begin.
    num: 2
    Jumped to label begin.
    num: 3
    Jumped to label begin.
    num: 4
    Jumped to label begin.
    num: 5
    Jumped to label begin.
    num: 6
    Jumped to label begin.
    num: 7
    Jumped to label begin.
    num: 8
    Jumped to label begin.
    num: 9
    Jumped to label begin.

    Jumped to label end.

**Ứng dụng của `goto`:**
+ Thoát ra khỏi nhiều vòng lặp lồng nhau.
Khi cần thoát ra khỏi nhiều vòng lặp lồng nhau ngay lập tức, việc sử dụng goto có thể đơn giản và hiệu quả hơn so với việc sử dụng các cờ (flags) hoặc các biến điều kiện.
Ví dụ:

        #include <stdio.h>

        int main() {
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (i * j > 50) {
                        goto end_loops; // Thoát khỏi tất cả các vòng lặp
                    }
                }
            }
            end_loops:
            printf("Exited the loops.\n");
            return 0;
        }

Giải thích: Thay vì phải check điều kiện ở 2 vòng lặp để `break` ta dùng lệnh goto để đơn giản và hiệu quả hơn. 

+ Xử lý lỗi (Error Handling)
Trong một số trường hợp, đặc biệt khi có nhiều bước xử lý tuần tự và có khả năng phát sinh lỗi, `goto` có thể được sử dụng để nhảy đến một đoạn mã chung để giải phóng tài nguyên hoặc thực hiện xử lý lỗi.

Ví dụ: 

    #include <stdio.h>
    #include <stdlib.h>

    int main() {
        FILE *file = fopen("example.txt", "r");
        if (file == NULL) {
            goto error;
        }

        // Các bước xử lý với file
        // ...

        fclose(file);
        return 0;

        error:
        printf("Error occurred, cleaning up.\n");
        // Các bước dọn dẹp nếu cần
        return 1;
    }
Giải thích: Trong trường hợp xảy ra lỗi khi mở file. Chương trình sẽ nhảy luôn đến nhãn `error` để thực hiện xử lý lỗi. 
### 5.2. Setjmp
`setjmp.h` là một thư viện trong ngôn ngữ lập trình C, cung cấp hai hàm chính là `setjmp` và `longjmp`được sử dụng để thực hiện xử lý ngoại lệ trong C.
+ `setjmp` là một macro trong C được định nghĩa trong thư viện `setjmp.h`. Nó lưu trạng thái hiện tại của luồng điều khiển tại điểm mà nó được gọi, bao gồm thông tin về con trỏ chương trình, con trỏ ngăn xếp và các thanh ghi CPU khác.
+ `longjmp` thường được dùng để quay trở lại điểm mà `setjmp` đã lưu trạng thái.

**Cú pháp setjmp:**
`int setjmp(jmp_buf env);`

`env`: Là một biến kiểu `jmp_buf`, được sử dụng để lưu trữ thông tin trạng thái tại thời điểm `setjmp` được gọi.
Nếu `setjmp` được gọi lần đầu tiên, nó sẽ trả về giá trị 0.
Nếu quay trở lại `setjmp` thông qua `longjmp`, nó sẽ trả về một giá trị khác 0 (thường là giá trị mà `longjmp` đã truyền vào).
Ví dụ:

    #include <stdio.h>
    #include <setjmp.h>
    jmp_buf buf;

    int main() {

        int setPoint = setjmp(buf);
            // No exception
        if (setPoint == 0) {
            printf("No exception \n");
            longjmp(buf, 1);
        } else if(setPoint == 1){
            // process exception 1
            printf("process exception 1.\n");
            longjmp(buf, 4);
        } else if(setPoint == 4)
        {
            // process exception 4
            printf("process exception 4.\n");
        }
        return 0;
    }

Giải thích:
+ `int setPoint = setjmp(buf);`: được gọi lần đầu tiên nên `setPoint` = 0, đồng thời sẽ lưu con trỏ chương trình, con trỏ ngăn xếp và các thanh ghi CPU khác vào `buf`.
+ `longjmp(buf, 1);`: Truyền giá trị vào `buf`, đồng thời quay trở lại điểm mà hàm `setjmp(buf)` được gọi là dòng `int setPoint = setjmp(buf);` => `setPoint = 1`

Ứng dụng của `setjmp-longjmp`
+ Xây dựng thư viện để xử lý ngoại lệ **(TRY, CATCH, THROW)** trên các ngôn ngữ bậc cao như Python, Javascript,...
+ 
Ví dụ:

    #include <stdio.h>
    #include <setjmp.h>

    jmp_buf buf;
    int exception_code;

    #define TRY if ((exception_code = setjmp(buf)) == 0) 
    #define CATCH(x) else if (exception_code == (x)) 
    #define THROW(x) longjmp(buf, (x))


    double divide(int a, int b) {
        if (b == 0) {
            THROW(1); // Mã lỗi 1 cho lỗi chia cho 0
        }
        return (double)a / b;
    }

    int main() {
        int a = 10;
        int b = 0;
        double result = 0.0;

        TRY {
            result = divide(a, b);
            printf("Result: %f\n", result);
        } CATCH(1) {
            printf("Error: Divide by 0!\n");
        }
        // Các xử lý khác của chương trình
        return 0;
    }

Giải thích: 

    #define TRY if ((exception_code = setjmp(buf)) == 0) 
    #define CATCH(x) else if (exception_code == (x)) 
    #define THROW(x) longjmp(buf, (x))
    
Macro `TRY` bản chất là 2 lệnh `exception_code = setjmp(buf)` và `if(exception_code == 0)`
Nếu `b == 0` gọi lệnh `THROW(1)` <=>  `longjmp(buf, 1)`. Chương trình nhảy đến đoạn `setjump` khởi tạo và gán giá trị cho `exception_code` = 1 sau đó thực hiện ngoại lệ. 
