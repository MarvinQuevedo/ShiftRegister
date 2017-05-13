# ShiftRegister
Facil manejo de los registros de desplazamiento (ShiftRegister) 74HC959.

La librería ShiftRegister ha sido creada con el único fin de proporcionar a los desarrolladores una forma fácil y cómoda de 
trabajar con los llamados "ShiftRegister" o registros de desplazamiento como los integrado 74HC959 de 8 bits para los cuales
ha sido desarrollado la libreria, sin embargo es compatible con integrados de 16 bits, simplemente indicando que se trabajará con 
dos integrados.

<table>
  <tr>
    <th>Nº</th>
    <th>Metodo</th>
    <th>Descripción</th>
    <th>Ejemplo</th>
  </tr>
  <tr>
    <td>1</td>
    <td>ShiftRegister(int latchPin, int clockPin, int dataPin, int howIc)</td>
    <td>Constructor donde se especifican los pines a utilizar para cada pin de los integrados, asi como tambien la cantidad de integrados que se van a emplear</td>
    <td>ShiftRegister shiftReg(10,11,12,1);</td>
  </tr>
<table>
