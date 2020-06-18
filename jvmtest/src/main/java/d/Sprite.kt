/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package d

/*

  @author mustafa
  Created on Jun 18, 2020
*/

enum class T(val v:Int) {
    D(0),
    B(1)
}

class Sprite {

    //const val LOCAL_MATRIX_DIRTY    = 1
    //const val ROTSKEW_DIRTY         = 1.shl(1)

    var state = T.D
    var flags = 0

    var x = 0f
        get() = field
        set(value) {
            if(value != field) {
                field = value
            }
        }

    var y = 0f
        get() = field
        set(value) {
            if(value != field) {
                field = value
            }
        }

}