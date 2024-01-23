uint16 set(uint16 value, uint16 n){
    mask = 0x01 << n;
    return value | mask;
}

uint16 clear(uint16 value, uint16 n){
    mask = 0x01 << n;
    return value & ~mask;
}

int16 toggle(uint16 value, uint16 n){
    mask = 0x01 << n;
    return value ^ mask;
}

void main(){
}