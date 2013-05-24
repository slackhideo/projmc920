#!/bin/sh

# Função que exibe o resultado
results() {
    if [ $? -eq 0 ]; then
        echo -e "\e[32mPassou!\e[m"
    else
        echo -e "\e[31mFalhou\e[m"
    fi
}

# Teste 1 (leitura e escrita de imagens)
echo -n "* Teste 1: "
rm -f flower_out.pgm
./testReadWrite
diff flower_check.pgm flower_out.pgm &> /dev/null
results


# Teste 2 (leitura de relações de adjacência)
echo -n "* Teste 2: "
rm -f adjRel_out
./testAdjRel > adjRel_out
diff adjRel_check adjRel_out &> /dev/null
results


# Teste 3 (leitura de kernel)
echo -n "* Teste 3: "
rm -f kernel_out
./testKernel > kernel_out
diff kernel_check kernel_out &> /dev/null
results


# Teste 4 (filtragem linear)
echo -n "* Teste 4: "
rm -f filter_out.pgm
./testFilter
diff filter_check.pgm filter_out.pgm &> /dev/null
results

# Teste 5 (kernels aleatórios)
echo "* Teste 5: Checar randKernels_out!"
rm -f randKernels_out
./testRandKernels > randKernels_out
