/*
 * Copyright (C) 2019 Digitoy Games.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package digiplay;
/*
#include <metal_stdlib>
using namespace metal;

struct InVertex2D {
	float3 pos 		[[attribute(0)]];
	uchar4 color	[[attribute(1)]];
};

struct Uniform2D {
	float4x4 projection;	
};

struct OutVertex2D {
	float4 pos [[position]];
	half4 color;	
};

vertex OutVertex2D vmain(InVertex2D inVertex [[stage_in]], constant Uniform2D &uniform [[buffer(0)]]) {
	OutVertex2D outVert;
	outVert.pos = uniform.projection * float4(inVertex.pos,1.0);
	outVert.color = half4(inVertex.color);
	return outVert;
}

fragment half4 fmain(OutVertex2D vert [[stage_in]], constant Uniform2D &uniforms [[buffer(0)]]) {
	return vert.color;
}
*/
/**
 *
 * @author mustafa
 */
public class Shader2D extends Shader {
/*
final static String VERT="attribute vec3 pos;\n" +
"            attribute vec2 uv;\n" +
"            attribute vec4 color;\n" +
"            //attribute vec3 m1;\n" +
"            //attribute vec3 m2;\n" +
"\n" +
"            uniform mat4 projection;\n" +
"            varying vec4 vColor;\n" +
"            varying vec2 vUv;\n" +
"            //varying vec4 vPos;\n" +
"\n" +
"            void main()\n" +
"            {\n" +
"                vColor = color;\n" +
"                vUv = uv;\n" +
"                //vPos = pos;\n" +
"                gl_Position = projection * vec4(pos.xyz, 1.0);\n" +
"            }";    

final static String FRAG="#ifdef GL_ES\n" +
"            precision mediump float;\n" +
"            #endif\n" +
"            varying vec4 vColor;\n" +
"            //varying vec2 vUv;\n" +
"            //varying vec4 vPos;\n" +
"            uniform sampler2D texture;\n" +
"\n" +
"            uniform lowp vec4 userVec4;\n" +
"\n" +
//"            __CODE__\n" +
"\n" +
"            void main()\n" +
"            {\n" +
"                gl_FragColor=vColor;\n" +
"            }";
*/
    final static String VERT = "#include <metal_stdlib>\n" +
"using namespace metal;\n" +
"\n" +
"struct InVertex2D {\n" +
"	float3 pos 		[[attribute(0)]];\n" +
"	uchar4 color	[[attribute(1)]];\n" +
"};\n" +
"\n" +
"struct Uniform2D {\n" +
"	float4x4 projection;	\n" +
"};\n" +
"\n" +
"struct OutVertex2D {\n" +
"	float4 pos [[position]];\n" +
"	half4 color;	\n" +
"};\n" +
"\n" +
"vertex OutVertex2D vmain(InVertex2D inVertex [[stage_in]], constant Uniform2D &uniform [[buffer(0)]]) {\n" +
"	OutVertex2D outVert;\n" +
"	outVert.pos = uniform.projection * float4(inVertex.pos,1.0);\n" +
"	outVert.color = half4(inVertex.color);\n" +
"	return outVert;\n" +
"}\n" +
"\n" +
"fragment half4 fmain(OutVertex2D vert [[stage_in]], constant Uniform2D &uniforms [[buffer(0)]]) {\n" +
"	return vert.color;\n" +
"}";
    final static String FRAG = "";
    
    public Shader2D() {
        super(VERT, FRAG);
        System.out.println("program = "+handle+" pos="+attrPos+" proj="+uniProjection+"  color="+attrColor);
    }

}