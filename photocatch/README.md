PhotoCatch
==========

PhotoCatch est un projet qui permet d'automatiser la prise de photo grâce à un capteur ultra-son et un arduino. 

README
------
Photocatch est composé de deux parties :

 * Un circuit électronique :
    * 1 arduino Uno
    * 4 afficheurs 7 segments
    * 1 servo moteur
    * 1 capteur à ultra-son
 * Un programme de contrôle.
 
AUTHORS
-------

* Yohann Lepage - @2xyo
* Quentin Rousseau - @quentinrousseau
 
INSTALL
-------

1. Réaliser les branchements en suivant le schéma [Fritzing](http://fritzing.org/ "Fritzing") 'docs/schema.fz'.
2. Uploader le fichier 'src/photocatch.ino' sur l'arduino.
3. Have fun.


COPYING / LICENSE
-----------------

	"THE BEER-WARE LICENSE" (Revision 42):
	Yohann and Quentin wrote this file. As long as you retain this notice you
	can do whatever you want with this stuff. If we meet some day, and you think
	this stuff is worth it, you can buy us a beer in return. Yohann & Quentin

BUGS
----

* L'afficheur indique des chiffres aléatoires à l'initialisation

ASCII ART
---------
                                                       ......,,,,,.                                         
                                               .:s5S53X;::,;irSS5;                                          
                                              ::9MXs;riA&GS2;.,;#S                                          
                                              :.39;     rXhi     :                                          
                                             .:.9B;      ABi     :                                          
                                               .rX5.   .A9s5,   ,:                                          
                                                 ..:,s9ABs  ,:::::                                          
                                                .,,,.                                                       
                                                .:,,.    ..                                                 
                                                .:,,.....,.                                                 
                                                .,,,,.   .                                                  
                                                .:,,,X2iXX.                                                 
                                                .:,.,BAhA3                                                  
                                                .,,.;A55&r                                                  
                                                .,, ;Ah9As                                                  
                                                .,, ;#22Ms                                                  
                                                .,..rBrrAX;                                                 
                                                 ,,,s#BB#&5:                                                
                                                 ,.s;,:,:rs .                                               
                                                .. r@@@@@@@i,.                                              
                                             .. . :H@@@@@@9si:                                              
                                            ,.rhM@#X@@##@Bi#BHS                                             
                                             ;@@@#MAM####M#@@@@2                                            
                    ,,    .,;r9M@@@@@MBBBBBBA#@MG&G23A######HA@@i.s,                                        
                    .:B@@53@@@@#MMBBBBBMBBBH@##A5XGXrr3HBBHH3&#@@@iXAX;                                     
                    .@@@@@#@#@BrrrrrsrrrrrrSB&MAirsX5r2GG&AAXG#M@@sG@@@3;                                   
                    X@hA#h5iG3ssi;i9i9hG&Gh3&HHAr:,:siss2XG&hA#@#@@B9S9M@.                                  
                    A@M#M39rSs:5BG2ss@#BM@AA#BBA;:, .,:riXGHAH##AH#@@@@@@rsMi                               
                    :@@BBh9h    &@;;@@S  ;M#MHB#BXAHB#@@##BHAABMA2X3&MMM@@@@@2                              
                    2@@AB&B@X;;rG@A@@@h..;#BB##@2 .;.,;,r.&#AHH&MGGhAMB#@@@r@@                              
                    S@#AH&B#@@@@#@@@@@@@@#@#M##@@@@@MHhX3S#@###HMMHAHM####@@@@S                             
                    r@#AABMGh9X&H#@@@@##M#@MMM##@@@@@@@@@@#M#M#M#B&Ah22BM3&@@@@                             
                    ,@#Hh&#MBHH####MMM##M#MB##@H@##@@#@@@@@####MBBB2;,rM#A,;@@@,                            
                     @#HH92XhAHAHM#BBMBH##B#MAA2sHMMA3@BhMM#@###MBMM#@@BMH  @@&.                            
                     @#HHHA&9X9B#@#BMBHABM##Aiiirrr;rrsSSi;;5H#AG@BHBBMA#A 5@B@; .                          
                     @@HAAAHHHH##@#BMBHA##M2si5SSSSSSSS5Ssrri5&MMMM#MBBH@AG@@@@  ,                          
                    r@HMHAAAAAAB#@#BMBHH#Grs2XXirrrsriS23X25iii&##MBHMBB#@@@@@:                             
                    22,@HAAAAAAB#@#BMBHB3i2333GXS22XX3X5A9X222S5A@#BMBHM#:#@@#                              
                    : ;@BAAAAAAB#@#BMBBAX&AAhS;,.   .,;i3&hXX3322MMHAHHMBs@@#.                              
                    S ;@BAAAAAAB#@#BMMBHB#2,              :XA3XX3BBAHHHM@@@:                                
                    , ;@BAAAHAHB###BBBGMH.                  r@H93BMHHHHM#&                                  
                      :@MAAHHHHB#@#M#9A&                     ,@#9AMHHB#@                                    
                      :@MAAHHHHB#@@#AA@                       ;@HXH#@@@i                                    
                       @@HHHHHHB#A. s@X                        @@22#&s.                                     
                       ;#@@@@@#@@   M@S                        @@B                                          
                         ,rS2XX2:   @@@                        @@@                                          
                                    3@@i                      H@@@                                          
                                     #@@i                    A@@@X                                          
                                      5@@@;                i@@##Mr.                                         
                                       X@@@@G:         .r#@@@@Bi.hS                                         
                                        h@@@@@@@@@##@@@@@@@@#M; .&2                                         
                                         i@@@@@@@@@@@@@@@##MB@..,As                                         
                                           G@@@@@@@@@@@@#MHMM3,..5                                          
                                             h@HM####MBHHB#B&S;;XH2;                                        
                                              sXSS5225S52X29H@r9@@@@,                                       
                                           . ,5@@BGG993hAM@@@H:X@@@@H                                       
                                           rSrG@@@@#XiiiH@@@3:.;M@@@@                                       
                                          ,,Hh,  ;H@##M##i,  sBss#M&@r                                      
                                       ;srr2@@@Br  .rS9:  ,X@@@@5  ;9@;                                     
                                      i@@@h.,@@@@@#X9@@29@@@@@@, ;@@&@@@@i                                  
                                ,s;rS,i@##@H  3M@@@@X..;2#@@@3  G#B@Mh@@@@rs:                               
                          .A@@@3i@#sH@@@##H@@. S##;         r.,@@MH#@@&;,s5s .:.                            
                     .,,. #@@@@@ss@# :@@BA#@@XsH:             H@###@@; ,&@3rsr2#rA@.                        
                   ,Br:Ghi@#&B##3 A@A .@,   rMs                rB2&3  2@@@;@A:@@@@r .,,                     
                ,  M@@;.#@@MHXh#& A@@#.r                         Xs r@@&@3S@ r@@@@:,3s;Xr..                 
             r::@@h@@@@, H@#@@@@3 ;ii2                             s@@@##;hS &#H#@@@A:H@M .,,.              
          .A@@@:,@@@@B@@ :@;;A&;                                     2@@@:Ar @@#@@@i 2@@@i.SX:r;            
       .. :@@B@G ;@#&@@@i ;                                            s@2@&,5&# BA s@A#@@@@;;@@,           
     ,;5G52@@M@@; #,                                                     .A@. #; ,;:@@@@@@@,.@@@@,.         
     2;s&@@@#@A@H,.                                                          #S   .r3:. s@; A#9@@. ,        
     #@: ,A@@A ,:                                                               ...      X,X@@#@@r;;:       
     M@@3  ,B@                                                                       .,. .;H2H@@#@@Br:      
     .@@@@X,,                                                                           ...  @@@Ai:,i3.     
