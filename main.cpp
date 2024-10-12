#include <iostream>
using namespace std;

/**
 * Imprime uma ajuda explicando como o programa deve ser usado.
 * @param program_name Nome do arquivo executável.
 */
void print_usage(string program_name) {
  cerr << "Usage:" << endl;
  cerr << '\t' << program_name << " <operation>" << endl;
  cerr << "Where <operation> can be:" << endl;
  cerr << '\t' << "gray: for creating a grayscale version of the original image." << endl;
  cerr << '\t' << "enlarge: for enlarging the original image 2x." << endl;
  cerr << '\t' << "reduce: for reducing the original image 2x." << endl;
  cerr << '\t' << "rotate: for rotating the image 90 degrees clockwise." << endl;
  cerr << '\t' << "sharp: for sharpening the image." << endl;
  cerr << '\t' << "blur: for blurring the image." << endl;
  cerr << endl;
  cerr << "The original image is read from the standart input and the transformed";
  cerr << "image is sent to the standart output." << endl;
}


/**
 * Função que transforma a cor da imagem para escala de cinza
*/
void gray(int linhas, int colunas){
  //leitura da imagem e alocação dos pixels em uma matriz
  int img[linhas][colunas][3];
  for (int i = 0; i < linhas; i++){
    for (int j = 0; j < colunas; j++){
      cin >> img[i][j][0] >> img[i][j][1] >> img[i][j][2];      
    }
  }

  for (int i = 0; i < linhas; i++){
    for (int j = 0; j < colunas; j++){
      //calculo da média dos valores r, g, b do pixel para formar a cor cinza
      int media = (img[i][j][0]  + img[i][j][1] + img[i][j][2])/3;
      //impresão dos novos valores r g b
      cout << media << " " << media << " " << media << " ";
      if (j == colunas-1){
        cout << endl;
      } 
    }
  }
}


/**
 * Função que amplia a imgem 2x
*/
void enlarge(int linhas, int colunas){
  //leitura da imagem e alocação dos pixels em uma matriz
  int img[linhas][colunas][3];
  for (int i = 0; i < linhas; i++){
    for (int j = 0; j < colunas; j++){
      cin >> img[i][j][0] >> img[i][j][1] >> img[i][j][2];      
    }
  }

  //cáculo da quantidade de linhas e colunas da imagem ampliada
  int qtd_linhas = (linhas * 2) - 1;
  int qtd_colunas = (colunas * 2) - 1;

  //matriz que recebe os pixels da ampliação
  int enlarge[256][256][3];
  int x = 0; //somado ao valor de j (equivalente as colunas da matriz), controla a intercalação das colunas
  int y = 0; //somado ao valor de i (equivalente as linhas da matriz), controla a intercalação das linhas

  //add pixels horizontalmente
  for (int i = 0; i < linhas; i++){
    x = 0;
    for (int j = 0; j < colunas; j++){
      //calculo novo pixel
      int r = (img[i][j][0] + img[i][j+1][0]) / 2;
      int g = (img[i][j][1] + img[i][j+1][1]) / 2;
      int b = (img[i][j][2] + img[i][j+1][2]) / 2;
      //add pixel criado a nova img
      enlarge[i+y][j+x][0] = img[i][j][0];
      enlarge[i+y][j+x][1] = img[i][j][1];
      enlarge[i+y][j+x][2] = img[i][j][2];
      x++;
      enlarge[i+y][j+x][0] = r;
      enlarge[i+y][j+x][1] = g;
      enlarge[i+y][j+x][2] = b; 
    }  
    y++;
  }

  //add pixels verticalmente
  for (int i = 1; i < qtd_linhas; i+=2){
    for (int j = 0; j < qtd_colunas; j++){
      //calculo novo pixel
      int r = (enlarge[i-1][j][0] + enlarge[i+1][j][0]) / 2;
      int g = (enlarge[i-1][j][1] + enlarge[i+1][j][1]) / 2;
      int b = (enlarge[i-1][j][2] + enlarge[i+1][j][2]) / 2;
      //add pixel criado a nova img
      enlarge[i][j][0] = r;
      enlarge[i][j][1] = g;
      enlarge[i][j][2] = b;
    }  
  }

  //imprimir imagem
  for (int i = 0; i < qtd_linhas; i++){
    for (int j = 0; j < qtd_colunas; j++){
      cout << enlarge[i][j][0] << " " << enlarge[i][j][1] << " " << enlarge[i][j][2] << " "; 
      if (j == qtd_colunas-1){
        cout << endl;
      }
    }
  }
}


/**
 * Função que reduz a imagem em 2x
*/
void reduce(int linhas, int colunas){
  //leitura da imagem e alocação dos pixels em uma matriz
  int img[linhas][colunas][3];
  for (int i = 0; i < linhas; i++){
    for (int j = 0; j < colunas; j++){
      cin >> img[i][j][0] >> img[i][j][1] >> img[i][j][2];      
    }
  }

  for (int l = 0; l < linhas; l+=2){
    for (int c = 0; c < colunas; c+=2){
      int r, g, b;
      r = 0;
      g = 0; 
      b = 0;
      for (int i = 0; i < 2; i++){ 
        for (int j = 0; j < 2; j++){ 
          r += img[l+i][c+j][0];
          g += img[l+i][c+j][1];
          b += img[l+i][c+j][2];
        } 
      }
      cout << r/4 << " " << g/4 << " " << b/4 << " ";   
    }
    cout << endl;
  }
}

/**
 * Função que rotaciona a img
*/
void rotate(int linhas, int colunas) {
  // criar uma nova matriz para armazenar a imagem rotacionada
  int rotated[72][128][3];

  //leitura da imagem e alocação dos pixels em uma matriz
  int img[linhas][colunas][3];
  for (int i = 0; i < 128; i++) {
    for (int j = 0; j < 72; j++) {
      cin >> img[i][j][0] >> img[i][j][1] >> img[i][j][2];
    }
  }

  // percorrer a imagem original e copiar os pixels para a nova matriz rotacionada
  for (int i = 0; i < 128; i++) {
    for (int j = 0; j < 72; j++) {
      rotated[j][linhas - i - 1][0] = img[i][j][0];
      rotated[j][linhas - i - 1][1] = img[i][j][1];
      rotated[j][linhas - i - 1][2] = img[i][j][2];
    }
  }

  // imprimir a nova matriz de pixels rotacionada
  for (int i = 0; i < 72; i++) {
    for (int j = 0; j < 128; j++) {
      cout << rotated[i][j][0] << " " << rotated[i][j][1] << " " << rotated[i][j][2] << " ";
    }
    cout << endl;
  }
}


/**
 * Função que aplica o filtro blur
*/
void blur(int linhas, int colunas) {
  // declaração das variáveis
  int img[linhas][colunas][3];
  int img_blur[linhas][colunas][3];

  //leitura da imagem e alocação dos pixels em uma matriz
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
        cin >> img[i][j][0] >> img[i][j][1] >> img[i][j][2];
    }
  }
  
  // definição da matriz de desfoque
  // é criada uma matriz Blurring com os valores de 1/9
  // com isso os pixels vizinhos tem um efeito de suavização sobre o pixel central
  float blurring[3][3] = {{1.0 / 9, 1.0 / 9, 1.0 / 9},
                          {1.0 / 9, 1.0 / 9, 1.0 / 9},
                          {1.0 / 9, 1.0 / 9, 1.0 / 9}};

  // dois loops para declarar a matriz img
  // para cada pixel da imagem original, um noco pixel é calculado aplicando o filtro
  for (int i = - 1; i < linhas - 1; i++) {
    for (int j = 1; j < colunas + 1; j++) {
      float r = 0.0, g = 0.0, b = 0.0;

      // aplicar o filtro na imagem
      // para cada posição do filtro, os valores RGB são multiplicados pelos coeficientes
      // e acumulados nas variavéis r, g, b.
      for (int k = -1; k <= 1; k++) {
        for (int l = -1; l <= 1; l++) {
          r += img[i + k][j + l][0] 
          * blurring[k + 1][l + 1];
          g += img[i + k][j + l][1] 
          * blurring[k + 1][l + 1];
          b += img[i + k][j + l][2] 
          * blurring[k + 1][l + 1];
        }
      }

      // o valor acumulado é atribuído ao canal de cor de pixel correspondente na matriz imgBlur
      img_blur[i][j][0] = r; img_blur[i][j][1] = g; img_blur[i][j][2] = b;
    }
  }
  // impressão da imagem filtrada
  // os valores são impressos na saída padrão
  // cada componente RGB é impresso separadamente
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      cout << img_blur[i][j][0] << " " << img_blur[i][j][1] << " " << img_blur[i][j][2] << " ";
    }
    cout << endl;
  }
}

/**
 * Função que aplica o filtro sharp
*/
void sharp(int linhas, int colunas) {
  // declaração das variavéis
  int img[linhas][colunas][3];
  int img_sharp[linhas][colunas][3];

  //leitura da imagem e alocação dos pixels em uma matriz
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      cin >> img[i][j][0] >> img[i][j][1] >> img[i][j][2];
    }
  }

  // seguindo a mesma lógica do blur
  // é criada uma matriz sharp de tamanho com os valores específicos para o filtro de nitidez.
  // essa matriz destaca os detalhes e bordas na imagem.
  int sharp[3][3] = {{0, -1, 0}, 
                    {-1, 5, -1}, 
                    {0, -1, 0}};
  
  //dois loops para declarar a matriz img
  //para cada pixel da imagem original, um novo pixel é calculado aplicando o filtro de nitidez.
  for (int i = 0; i < linhas -1; i++) {
    for (int j = - 1; j < colunas == 1; j++) {
      int r = 0, 
          g = 0, 
          b = 0;

      // aplicar o filtro na imagem
      // para cada posição do filtro, os valores RGB são multiplicados pelos coeficientes
      // os valores acumulados são atribuídos aos canais de cor do pixel correspondente na matriz imgSharp.
      for (int k = -1; k <=  1; k++) {
        for (int l = -1; l <=  1; l++) {
          r += img[i + k][j + l][0] 
          * sharp[k + 1][l + 1];
          g += img[i + k][j + l][1] 
          * sharp[k + 1][l + 1];
          b += img[i + k][j + l][2] 
          * sharp[k + 1][l + 1];
        }
      }

      // O valor acumulado é atribuído ao canal de cor de pixel correspondente na matriz imgBlur
      img_sharp[i][j][0] = r; img_sharp[i][j][1] = g; img_sharp[i][j][2] = b;
    }
  }
  // Imprimir a imagem com nitidez
  // Impressão da imagem na saída padrão
  for (int i = 0; i < 128; i++) {
    for (int j = 0; j < 72; j++) {
      cout << img_sharp[i][j][0] << " " << img_sharp[i][j][1] << " " << img_sharp[i][j][2] << " ";
    }
    cout << endl;
  }
}


/**
 * Função principal: ponto de partida do programa
 */
int main(int argc, char* argv[]) {
  if (argc != 2) {
    // se não houver 2 argumentos, então o programa está sendo usado incorretamente.
    // deve-se portanto imprimir como usá-lo.
    print_usage(argv[0]);
  }
  else {
    //argumento que recebe a operação a ser executada
    string operacao = argv[1];

    //leutura do cabeçalho da imagem
    string formato, rgb_max;
    int linhas, colunas;
    cin >> formato;
    cin >> colunas >>  linhas;
    cin >> rgb_max;

    //chamada das funções de acordo com a operação solicitada
    if (operacao == "gray"){
      cout << formato << endl << colunas << " " << linhas << endl << rgb_max << endl;
      gray(linhas, colunas);
    } else if (operacao == "enlarge"){
      cout << formato << endl << colunas*2 - 1 << " " << linhas*2 - 1<< endl << rgb_max << endl;
      enlarge(linhas, colunas);
    } else if (operacao == "reduce"){
      cout << formato << endl << colunas/2 << " " << linhas/2 << endl << rgb_max << endl;
      reduce(linhas, colunas);
    }else if (operacao == "rotate"){
      cout << formato << endl << linhas << " " << colunas << endl << rgb_max << endl;
      rotate(linhas, colunas);
    }else if (operacao == "sharp"){
      cout << formato << endl << colunas << " " << linhas << endl << rgb_max << endl;
      sharp(linhas, colunas);
    } else {
      cout << formato << endl << colunas << " " << linhas << endl << rgb_max << endl;
      blur(linhas, colunas);
    }
  }

  return 0;
}