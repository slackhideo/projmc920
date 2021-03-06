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
diff -q flower_check.pgm flower_out.pgm &> /dev/null
results


# Teste 2 (leitura de relações de adjacência)
echo -n "* Teste 2: "
rm -f adjRel_out
./testAdjRel > adjRel_out
diff -q adjRel_check adjRel_out &> /dev/null
results


# Teste 3 (leitura de kernel)
echo -n "* Teste 3: "
rm -f kernel_out
./testKernel > kernel_out
diff -q kernel_check kernel_out &> /dev/null
results


# Teste 4 (filtragem linear)
echo -n "* Teste 4: "
rm -f filter_out.pgm
./testFilter
diff -q filter_check.pgm filter_out.pgm &> /dev/null
results

# Teste 5 (kernels aleatórios)
echo "* Teste 5: Testando... Cheque o arquivo randKernels_out para conferir 
o resultado do teste!"
rm -f randKernels_out
./testRandKernels > randKernels_out

# Teste 6 (Pooling)
echo "* Teste 6: Testando Pooling:"
rm -f flower_out_pooling.pgm
rm -f flower_out_pooling_max.pgm
rm -f flower_out_pooling_min.pgm
rm -f flower_out_pooling_mean.pgm
rm -f flower_out_pooling_norm2.pgm
./poolingTest

# Teste 7 (Normalização)
echo "* Teste 7: Testando normalização:"
rm -f flower_out_normalization.pgm
./testNormalization

# Teste 8 (kernels aleatórios 2)
echo "* Teste 8: Testando... Cheque o arquivo randKernels_out2 para conferir 
o resultado do teste!"
rm -f randKernels_out2
./testRandKernels2 > randKernels_out2
