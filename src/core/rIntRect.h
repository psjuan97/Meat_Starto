#pragma once

    class rIntRect {
        friend class renderEngine;
        public:
            rIntRect();                             //CONSTRUCTOR 1 (NO UTILIZAR)
            //X,Y,W,H
            rIntRect(int x, int y, int w, int h);   //CONSTRUCTOR 2
            
            bool contains(float x, float y);        //TRUE: INTRECT CONTIENE AL PUNTO P(X,Y)
            int left;
            int top;
            int widht;
            int height;
            
            void setTop(int t);
            void setLeft(int l);
            void setWidth(int w);
            void setHeight(int h);
        private:

     };
