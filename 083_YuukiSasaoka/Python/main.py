# ① 128バイトの初期バイナリデータを作成（全部 0x00）
data = bytearray(128)

# ★ 変更前をコピーして保存
before_data = data.copy()

# ② 一部を書き換える
data[10] = 0xA1
if data[10] == 0xAA:
    data[11] = 0xBB
data[12] = 0xCC
data[13] = 0xDD


# ★ 変更後をコピー
after_data = data.copy()

# ③ 16バイトずつ16進数で表示する関数
def dump_hex(title, buf):
    print(f"\n--- {title} ---")
    for i in range(0, len(buf), 16):
        chunk = buf[i:i+16]
        hex_str = " ".join(f"{b:02X}" for b in chunk)
        print(f" {hex_str}")

# 変更前・変更後を表示
dump_hex("BEFORE", before_data)
dump_hex("AFTER", after_data)

# ④ 変更された内容だけ表示
print("\n--- CHANGED BYTES ---")
for i, (b, a) in enumerate(zip(before_data, after_data)):
    if b != a:
        print(f"offset {i:03d} (0x{i:02X}): {b:02X} -> {a:02X}")
