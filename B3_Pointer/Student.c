#include <stdio.h>
#include <string.h>

typedef struct {
    char ten[50];
    float diemTrungBinh;
    int id;
} SinhVien;


int stringCompare(const char *str1, const char * str2)
{
    // check alpha b
    // ưu tiên A - Z. 
    // nếu trùng chữ thì ưu tiên tên có kí tự ít hơn
    // ví dụ Hoa và Hoàng -> ưu tiên Hoa.

    while (*str1 && (*str1 == *str2))
    {
        str1 ++;
        str2 ++;
    }
    // trả về giá trị chênh lệch 
    return *(const unsigned char*) str1 - *(const unsigned char*) str2;
//    return *(const char*) str1 - *(const char*) str2;
}


// hàm so sánh theo tên
int compareByName(const void *a, const void *b)
{
    // ép kiểu do con trỏ void trỏ được nhưng không ép kiểu thì không đọc được. 
    SinhVien *sv1 = (SinhVien *)a;
    SinhVien *sv2 = (SinhVien *)b;

    // trả về giá trị chênh lệch 
    return stringCompare(sv1 -> ten, sv2 -> ten);
}



// Hàm so sánh theo điểm trung bình
int compareByDiemTrungBinh(const void *a, const void *b)
{

    SinhVien *sv1 = (SinhVien *)a;
    SinhVien *sv2 = (SinhVien *)b;


    if(sv1 -> diemTrungBinh > sv2->diemTrungBinh)
    {
        return 1;
    }
    return 0;
}


int compareByID(const void *a, const void *b)
{
    SinhVien *sv1 = (SinhVien *)a;
    SinhVien *sv2 = (SinhVien *)b;

    // trả về giá trị chêch lệch 
    return sv1 -> id - sv2 -> id;
}

// Hàm sắp xếp chung
// Bubble Sort
void sort(SinhVien array[], size_t size, int (*compareFunc)(const void *, const void *)) {
   int i, j;
   SinhVien temp;
   for (i = 0; i < size-1; i++)    
       for (j = i+1; j < size; j++)
           if (compareFunc(array+i, array+j)>0) {  // name, id, diem trung binh 
            // ví dụ compareByName(array+i, array+j)
            // do array là địa chỉ đầu tiên của phần tử đầu nên array + i là địa chỉ của phần tử thứ i.
               temp = array[i];
               array[i] = array[j];
               array[j] = temp;
           }
}


void display(SinhVien *array, size_t size) {
   for (size_t i = 0; i < size; i++) {
       printf("ID: %d, Ten: %s, Diem Trung Binh: %.2f\n", array[i].id, array[i].ten, array[i].diemTrungBinh);
   }
   printf("\n");
}

int main() {
   SinhVien danhSachSV[] = {
       {  
           .ten = "Hoang",
           .diemTrungBinh = 7.5,
           .id = 100
       },
       {
           .ten = "Tuan",
           .diemTrungBinh = 4.5,
           .id = 101
       },
       {
           .ten = "Vya",
           .diemTrungBinh = 6.8,
           .id = 102},
       {  
           .ten = "Ngan",
           .diemTrungBinh = 5.6,
           .id = 10
       },
        {  
           .ten = "Hoa",
           .diemTrungBinh = 5.0,
           .id = 9
       },
   };
   size_t size = sizeof(danhSachSV) / sizeof(danhSachSV[0]);

   printf("sap xep theo ten\n");
   // Sắp xếp theo tên
   sort(danhSachSV, size, compareByName);

   display(danhSachSV, size);

    printf("sap xep theo diem trung binh\n");
   // Sắp xếp theo điểm trung bình
   sort(danhSachSV, size, compareByDiemTrungBinh);

   display(danhSachSV, size);

    printf("sap xep theo ID\n");
   // Sắp xếp theo ID
   sort(danhSachSV, size, compareByID);

   display(danhSachSV, size);

   return 0;
}
