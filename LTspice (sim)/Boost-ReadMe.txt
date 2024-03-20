BOOST CONVERTER

-> la corrente cresce e decresce linearmente solo nel breve periodo (le curve a lungo periodo sono esponenziali)
   dunque occorre lavorare a alte frequenze di switching; almeno 1kHz o oltre. 

-> Il transistore MOSFET va scelto in modo che sia BASSA resistenza quando on e ALTA resistenza quando off.

-> Il diodo va scelto in modo da reggere i picchi di tensione e di corrente. 

-> Il boost converter converte la TENSIONE E LA CORRENTE da ingresso a uscita. Dunque aumentare la tensione significa diminuire la corrente
   perchè la potenza non può aumentare, dunque occorre dimensionare considerando che la corrente richiesta per aumentare la tensione
   sarà MOLTA di più, corrente aggiuntiva che va a finire su L, C e il diodo. 

-> Nella scelta dei parametri L e C occorre considerare i casi peggiori. Per esempio una tensione di ingresso più alta del dovuto
   significa minore duty cycle dunque maggiore ripple, per cui occorre scegliere L più alta. 
   Nel mio caso il DUTY CYCLE è variabile, dunque occorre consiederare la scelta di L e C in base al caso di duty cycle peggiore
   (probabilmente il caso peggiore è il duty-cycle più basso).
   Oltre a questo c'è da considerare il rendimento che non è max duqnue potenza maggiore in ingresso a parità di uscita, dunque considerare
   una percentuale in più nella corrente su L. 


* Ho scelto 20kHz come frequenza di switching. Frequenze piú basse rischiano di portare il boost in discontinuous mode, mentre frequenze piú       
  alte limitano il duty cycle max in quanto l'amplificatore operazionale usato come driver non riesce a seguire lo slew rate e perde us di Ton 
  che diventano importanti a alte frequenze.   