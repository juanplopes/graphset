/**
 * Originally grabbed from the official RaphaelJS Documentation
 * http://raphaeljs.com/graffle.html
 * Adopted (arrows) and commented by Philipp Strathausen http://blog.ameisenbar.de
 * Licenced under the MIT licence.
 */

/**
 * Usage:
 * connect two shapes
 * parameters: 
 *      source shape [or connection for redrawing], 
 *      target shape,
 *      style with { fg : linecolor, bg : background color, directed: boolean }
 * returns:
 *      connection { draw = function() }
 */
Raphael.fn.connection = function (obj1, obj2, style) {
    var selfRef = this;
    /* create and return new connection */
    var edge = {/*
        from : obj1,
        to : obj2,
        style : style,*/
        draw : function() {
            /* get bounding boxes of target and source */
            var bb1 = obj1.items[0].node.getBBox();
            var bb2 = obj2.items[0].node.getBBox();

            var x1 = bb1.x + bb1.width / 2,
                y1 = bb1.y + bb1.height/2,
                x4 = bb2.x + bb2.width / 2,
                y4 = bb2.y + bb2.height/2;
                
            /* assemble path and arrow */
            var path = ["M", x1.toFixed(3), y1.toFixed(3), "L", x4.toFixed(3), y4.toFixed(3)].join(",");
            
            var width = (obj1.isSelected || obj2.isSelected) ? '3px' : '1px';
            var color = (obj1.isSelected || obj2.isSelected) ? '#D9534F' : 'black'
            
            if (!edge.fg)
                edge.fg = selfRef.path(path).attr({stroke: color, fill: "none", 'stroke-width': width}).toBack();
            else
                edge.fg.attr({path:path,'stroke-width': width, stroke: color});
    
        
            var padding = 3;
            if (!edge.label) {
                edge.label = selfRef.text((x1+x4)/2, (y1+y4)/2, style.label).attr({fill: "white", 'font-weight': 'bold', "font-size": style["font-size"] || "12px"});
                var box = edge.label.getBBox();
                edge.rect = selfRef.rect(box.x-padding, box.y-padding, box.width+2*padding, box.height+2*padding).attr({r:4, fill: '#00aff0', stroke:'#00aff0'});
                edge.label.toFront();
            } else {
                edge.label.attr({x:(x1+x4)/2, y:(y1+y4)/2});
                var box = edge.label.getBBox();
                edge.rect.attr({x:box.x-padding, y:box.y-padding});
            }
        }
    }
    edge.draw();
    return edge;
};
//Raphael.prototype.set.prototype.dodo=function(){console.log("works");};
