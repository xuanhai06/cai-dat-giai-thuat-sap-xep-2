#include <iostream>
#include <string>

using namespace std;

const int MAX_SINH_VIEN = 100;

struct SinhVien
{
    int MaSV;
    string HoTen;
    int NamSinh;
    float DiemTrungBinh;
};

void NhapThongTin(SinhVien danhSach[], int& n)
{
    cout << "Nhap vao so luong sinh vien (toi da " << MAX_SINH_VIEN << "): ";
    cin >> n;
    if (n > MAX_SINH_VIEN)
	{
        cout << "So luong sinh vien vuot qua gioi han! Gan max la " << MAX_SINH_VIEN << ".\n";
        n = MAX_SINH_VIEN;
    }

    for (int i = 0; i < n; i++) {
        cout << "Nhap vao ma sinh vien thu " << (i + 1) << " : ";
        cin >> danhSach[i].MaSV;

        cout << "Nhap vao ho ten sinh vien thu " << (i + 1) << " : ";
        cin.ignore(); 
        getline(cin, danhSach[i].HoTen);

        cout << "Nhap vao nam sinh sinh vien thu " << (i + 1) << " : ";
        cin >> danhSach[i].NamSinh;

        cout << "Nhap vao diem trung binh cua sinh vien " << (i + 1) << " : ";
        cin >> danhSach[i].DiemTrungBinh;
    }
}

void HienThiThongTin(const SinhVien danhSach[], int n)
{
    cout << "\nDanh sach sinh vien:\n";
    for (int i = 0; i < n; i++)
	{
        cout << "Ma SV: " << danhSach[i].MaSV << ", Ho Ten: " << danhSach[i].HoTen 
             << ", Nam Sinh: " << danhSach[i].NamSinh 
             << ", Diem TB: " << danhSach[i].DiemTrungBinh << endl;
    }
}

void SapXepChon(SinhVien danhSach[], int n)
{
    for (int i = 0; i < n - 1; i++)
	{
        int maxIndex = i;
        for (int j = i + 1; j < n; j++)
		{
            if (danhSach[j].DiemTrungBinh > danhSach[maxIndex].DiemTrungBinh)
			{
                maxIndex = j;
            }
        }
        swap(danhSach[i], danhSach[maxIndex]);
    }
}

void Ghep(SinhVien danhSach[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    SinhVien leftList[MAX_SINH_VIEN], rightList[MAX_SINH_VIEN];

    for (int i = 0; i < n1; i++)
        leftList[i] = danhSach[left + i];
    for (int j = 0; j < n2; j++)
        rightList[j] = danhSach[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftList[i].DiemTrungBinh >= rightList[j].DiemTrungBinh)
		{
            danhSach[k++] = leftList[i++];
        } else {
            danhSach[k++] = rightList[j++];
        }
    }

    while (i < n1)
	{
        danhSach[k++] = leftList[i++];
    }

    while (j < n2)
	{
        danhSach[k++] = rightList[j++];
    }
}

void SapXepTron(SinhVien danhSach[], int left, int right)
{
    if (left < right)
	{
        int mid = left + (right - left) / 2;

        SapXepTron(danhSach, left, mid);
        SapXepTron(danhSach, mid + 1, right);
        Ghep(danhSach, left, mid, right);
    }
}

int YenCau(SinhVien danhSach[], int left, int right)
{
    SinhVien pivot = danhSach[right];
    int i = left - 1;

    for (int j = left; j < right; j++)
	{
        if (danhSach[j].DiemTrungBinh > pivot.DiemTrungBinh)
		{
            i++;
            swap(danhSach[i], danhSach[j]);
        }
    }
    swap(danhSach[i + 1], danhSach[right]);
    return i + 1;
}

void SapXepNhanh(SinhVien danhSach[], int left, int right)
{
    if (left < right)
	{
        int pi = YenCau(danhSach, left, right);
        SapXepNhanh(danhSach, left, pi - 1);
        SapXepNhanh(danhSach, pi + 1, right);
    }
}

int main()
{
    SinhVien danhSach[MAX_SINH_VIEN]; 
    int n;

    NhapThongTin(danhSach, n); 

    cout << "\nDanh sach sinh vien truoc khi sap xep:\n";
    HienThiThongTin(danhSach, n); 

    SapXepChon(danhSach, n);
    cout << "\nDanh sach sinh vien sau khi sap xep theo diem TB (Sap xep chon):\n";
    HienThiThongTin(danhSach, n);

    SapXepTron(danhSach, 0, n - 1);
    cout << "\nDanh sach sinh vien sau khi sap xep theo diem TB (Sap xep tron):\n";
    HienThiThongTin(danhSach, n); 

    SapXepNhanh(danhSach, 0, n - 1);
    cout << "\nDanh sach sinh vien sau khi sap xep theo diem TB (Sap xep nhanh):\n";
    HienThiThongTin(danhSach, n); 

    return 0;
}
