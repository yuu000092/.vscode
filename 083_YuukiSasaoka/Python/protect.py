class protect:
    def __init__(self):
        pass

    #byteを16bitにし、中身を編集して再度byteに戻す
    def access_protect(self):
        data = b"0x02020902111a"
        
        #dataの5番目と６番目を取り出し、bitにする
        byte1 = data[4:6]
        #bit変換
        bit1 = bin(int(byte1, 16))[2:].zfill(8)
        #16bitのうち、2:6bit目を編集
        edited_bit1 = bit1[:2] + '0011' + bit1[6:]
        #再度byteに戻す
        edited_byte1 = hex(int(edited_bit1, 2))[2:].zfill(2)
        
        #変更前と変更後の表示
        print(f"Before: {byte1}")
        print(f"After: {edited_byte1}")
    
    
if __name__ == "__main__":
    pro = protect()
    pro.access_protect()