def main():
    data = [47, 61, 36, 52, 56, 33, 92]
    record = set()
    for c in range(1, 100):
        flag = True
        for a in data:
            x = ((10 * a + 4) % c) % 7
            if x in record:
                flag = False
                break
            record.add(x)
        if flag:
            print(c)
            break
        record.clear()

if __name__ == '__main__':
    main()