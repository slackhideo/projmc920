#!/bin/sh

# Função que exibe o resultado
results() {
    if [ $? -eq 0 ]; then
        echo -e "\e[32mPassou!\e[m"
    else
        echo -e "\e[31mFalhou\e[m"
    fi
}

# Teste 1
echo -n "* Teste 1 (leitura e escrita): "
rm -f flower_out.pgm
./testReadWrite
diff flower_check.pgm flower_out.pgm &> /dev/null
results


# Teste 2
echo -n "* Teste 2 (relações de adjacência): "
rm -f adjRel_out
./testAdjRel > adjRel_out
diff adjRel_check adjRel_out &> /dev/null
results
