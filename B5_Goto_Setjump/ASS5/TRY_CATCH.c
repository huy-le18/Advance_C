#include <stdio.h>
#include <setjmp.h>

enum ErrorCodes {
    NO_ERROR,
    FILE_ERROR,
    NETWORK_ERROR,
    CALCULATION_ERROR,
    AFTER_FIXED_ERROR
};

enum NetworkError {
    NO_NETWORK_ERROR,
    HAS_NETWORK_ERROR
};

enum FileError {
    NO_FILE_ERROR,
    HAS_FILE_ERROR
};

enum CalcualtionError {
    NO_CALCULATION_ERROR,
    HAS_CALCULATION_ERROR
};


jmp_buf buf;
int exception_code;
char* error_message = NULL;

int network_error = HAS_NETWORK_ERROR;
int file_error = NO_FILE_ERROR;
int calcualtion_error = NO_CALCULATION_ERROR;

#define TRY if ((exception_code = setjmp(buf)) == NO_ERROR) 
#define CATCH(x) else if (exception_code == (x)) 
#define THROW(x, error_mes) error_message = error_mes; longjmp(buf, (x));


void readFile(){
    printf("1. Reading file ...\n");

    /* đoạn code chỗ này sẽ là kiểm tra lại hoạt động file
        nếu phát hiện lỗi thì gán file_error = HAS_FILE_ERROR
        còn không thì gán         file_error = NO_FILE_ERROR
    */


    if(file_error == NO_FILE_ERROR)
    {
        // to do
        printf("Handle data from file successful!!!\n\n");
    }
    else if(file_error == HAS_FILE_ERROR)
    {
        THROW(FILE_ERROR, "Error read file: file not exist!!");
    }
}

void networkOperation(){
    // Bổ sung chương trình 
    printf("2. Connect to Network ...\n");

    if(network_error == NO_NETWORK_ERROR)
    {
        // to do
        printf("Connected successful!!!\n\n");
    }
    else if(network_error == HAS_NETWORK_ERROR)
    {
        THROW(NETWORK_ERROR, "Error network: fail connected");
    }
}

void calculateData(){
    // Bổ sung chương trình 
    printf("3. Calculating ...\n");

    if(calcualtion_error == NO_CALCULATION_ERROR)
    {
        // to do
        printf("Calculated successful!!!\n\n");
    }
    else if(calcualtion_error == HAS_CALCULATION_ERROR)
    {
        THROW(CALCULATION_ERROR, "invalid value");
    }
}



int main()
{

    TRY {
         readFile();
         networkOperation();
         calculateData();
    }
    CATCH(FILE_ERROR)
    {
        /* đoạn code chỗ này sẽ là thông báo lỗi */
        printf("%s\n", error_message);

        /* đoạn code chỗ này sẽ là sửa lỗi hoặc kiểm tra lại */
        printf("fixing file error.................\n");

        /* sửa xong thì cập nhập lại cờ  file_error*/
        file_error = NO_FILE_ERROR;

        /* nhảy đến case: AFTER_FIXED_ERROR để check lại */
        THROW(AFTER_FIXED_ERROR, "Successfully fixed file error!!!\n");
    }
    CATCH(NETWORK_ERROR)
    {
        /* đoạn code chỗ này sẽ là thông báo lỗi */
        printf("%s\n", error_message);

        /* đoạn code chỗ này sẽ là sửa lỗi hoặc kết nối lại */
        printf("Connecting again.................\n");
        
        /* sửa xong thì cập nhập lại cờ  file_error*/
        network_error = NO_NETWORK_ERROR;

        /* nhảy đến case: AFTER_FIXED_ERROR để check lại */
        THROW(AFTER_FIXED_ERROR, "Connected successfully!!!\n");

    }
    CATCH(CALCULATION_ERROR)
    {

        /* đoạn code chỗ này sẽ là thông báo lỗi */
        printf("%s\n", error_message);

        /* đoạn code chỗ này sẽ là yêu cầu người dùng nhập lại giá trị cho mẫu số khác 0*/
        printf("Not allow enter 0 for denominator!!! Enter again\n");
        
        printf("valid value\n");
        /* sửa xong thì cập nhập lại cờ  file_error*/
        calcualtion_error = NO_CALCULATION_ERROR;

        /* nhảy đến case: AFTER_FIXED_ERROR để check lại */
        THROW(AFTER_FIXED_ERROR, "The denominator has been changed!!!\n");

    }
    CATCH(AFTER_FIXED_ERROR)
    {
        printf("%s\n", error_message);
        // check again

        readFile();
        networkOperation();
        calculateData();
    }

    return 0;
}