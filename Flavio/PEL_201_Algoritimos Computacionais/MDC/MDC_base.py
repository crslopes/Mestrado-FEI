def mdc_div(a, b, Tn):
    if a > b:  # 1             (1)
        dividendo = a  # 1             (2)
        divisor = b  # 1             (3)
    else:
        dividendo = b  # 1             (2)
        divisor = a  # 1             (3)
    resto = -1  # 1             (4)
    Tn = Tn + 3  # 1             (5)
    while resto != 0:  # n - 1         (n+6)
        resto = dividendo % divisor  # n       (n+6)
        dividendo = divisor  # n       (n+6)
        divisor = resto  # n
        Tn = Tn + 5  # n
    return dividendo, Tn  # 1


# f(n) =

def main():
    print("Entre com os valores máximos e mínimos para encontrar o MDC")
    n1orig = int(input("\nLimite inferior Número: "))
    n2orig = int(input("\nLimite Superior Número: "))

    Tn = 2
    Tn = 2
    n1 = n1orig
    n2 = n2orig
    (ret_mdc, Tn) = mdc_div(n1, n2, Tn)
    print("O MDC entre ", n1, " e ", n2, " é ", ret_mdc, "\n T(n)=",Tn)

main()
