#include <stdio.h>
#include <stdint.h>

// Hàm lấy bậc của đa thức (vị trí bit cao nhất bằng 1)
int get_degree(uint16_t poly) {
    if (poly == 0) return -1;
    int deg = 0;
    while (poly >>= 1) {
        deg++;
    }
    return deg;
}

// Hàm chia đa thức trong GF(2), trả về thương (q) và dư (r) qua con trỏ
void poly_div(uint16_t a, uint16_t b, uint16_t *q, uint16_t *r) {
    *q = 0;
    *r = a;
    int deg_b = get_degree(b);
    
    if (deg_b < 0) return; // Tránh lỗi chia cho 0

    while (get_degree(*r) >= deg_b) {
        int shift = get_degree(*r) - deg_b;
        *q ^= (1 << shift);     // Cộng (XOR) phần thương
        *r ^= (b << shift);     // Trừ (XOR) phần đã chia
    }
}

// Hàm nhân đa thức trong GF(2)
uint16_t poly_mul(uint16_t a, uint16_t b) {
    uint16_t p = 0;
    while (a > 0) {
        if (a & 1) {
            p ^= b;
        }
        b <<= 1;
        a >>= 1;
    }
    return p;
}

// Thuật toán Euclidean mở rộng trên GF(2^10)
uint16_t extended_euclidean_gf2(uint16_t m, uint16_t a) {
    uint16_t r1 = m, r2 = a;
    uint16_t t1 = 0, t2 = 1;
    uint16_t q, r, t;
    int step = 1;

    printf("| Buoc | r1   | r2   | q    | r    | t1   | t2   | t    |\n");
    printf("|------|------|------|------|------|------|------|------|\n");

    while (r2 > 0) {
        poly_div(r1, r2, &q, &r);
        
        // Tính t = t1 - (q * t2). Trong GF(2), phép trừ là XOR
        t = t1 ^ poly_mul(q, t2); 
        
        printf("| %-4d | %-4u | %-4u | %-4u | %-4u | %-4u | %-4u | %-4u |\n", 
               step, r1, r2, q, r, t1, t2, t);
        
        // Cập nhật giá trị cho vòng lặp tiếp theo
        r1 = r2;
        r2 = r;
        t1 = t2;
        t2 = t;
        step++;
    }

    printf("\n=> Nghich dao nhan la: %u\n\n", t1);
    return t1;
}

int main() {
    // Đa thức m(x) = x^10 + x^3 + 1 biểu diễn dưới dạng số nguyên
    // 10000001001 (nhị phân) = 1033 (thập phân)
    uint16_t m = 1033;
    
    printf("=== TIM NGHICH DAO CUA a = 523 ===\n");
    extended_euclidean_gf2(m, 523);
    
    printf("=== TIM NGHICH DAO CUA b = 1015 ===\n");
    extended_euclidean_gf2(m, 1015);

    return 0;
}
