(function() {
    var state = {
        id: null,
        filtered: null
    };
    
    function setUrl() {
        window.location.hash = [state.id, state.filter||''].join('/');
    }

    function popc(i) {
         i = i - ((i >> 1) & 0x55555555);
         i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
         return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
    }

    function setGraph(index) {
        state.id = index;
        setUrl();
    
        var graph = data[index];
        var cont = $('.main-graph').html('');
        var g = new Graph();

        for(var i=0; i<graph.G.length; i++) {
            var items = [];
            for(var j=0; j<graph.b; j++) {
                if (graph.S[i] & (1<<j))
                    items.push(j+1);
            }
            
            g.addNode('a'+i, { index: (graph.O||{})[i], label: items, render: function(r, n) {
                var set = r.set()
                    .push(r.rect(n.point[0]-30, n.point[1]-30, 60, 60).attr({"fill": "white", r : "12px", "stroke-width" : n.distance == 0 ? "3px" : "1px" }));
                    
                if (n.index != null) {
                    set = set
                        .push(r.rect(n.point[0]+30-16, n.point[1]-30, 16, 16).attr({"fill": "#D9534F", r : "4px", "stroke-width" : n.distance == 0 ? "3px" : "1px" }))
                        .push(r.text(n.point[0]+30-8, n.point[1]-22, ''+n.index).attr({'fill':'white', 'font-weight': 'bold'}));
                }
                
                if (n.label.length > 3) {
                     var aa = n.label.slice(0, (n.label.length+1)/2),
                         bb = n.label.slice((n.label.length+1)/2);
                     set = set
                         .push(r.text(n.point[0], n.point[1]-10, aa.join(' ')).attr('font-weight', 'bold'))
                         .push(r.text(n.point[0], n.point[1]+10, bb.join(' ')).attr('font-weight', 'bold'));
                } else {
                     set = set
                         .push(r.text(n.point[0], n.point[1], n.label.join(' ')).attr('font-weight', 'bold'));
                }
                return set;
            }});
   
        }
        for(var i=0; i<graph.G.length; i++) {
            for(var j=i+1; j<graph.G.length; j++) {
                var a = popc(graph.S[i]&graph.S[j]);
                var b = popc(graph.S[i]|graph.S[j]);

                if (graph.G[i] & (1<<j))
                    g.addEdge('a' + i, 'a' + j, {label:a+'/'+b});
            }
        }
         
        var layouter = new Graph.Layout.Spring(g);
        layouter.layout();
         
        var renderer = new Graph.Renderer.Raphael('canvas', g, cont.width(), cont.height());
        renderer.draw();
    }

    function arrayEquals(array1, array2) {
        return (array1.length == array2.length) && array1.every(function(element, index) {
            return element == array2[index]; 
        });
    }

    function filter(text) {
        state.filter = text;
        setUrl();
    
        text = text.trim();
        var dSearch = null, nSearch = null, bSearch = null, iSearch = null;
        
    
        if (text[0] == 'n' || text[0] == 'b') {
            splitted = text.split(/[^\d\w]+/);

            for(var i=0; i<splitted.length; i++) {
                if (splitted[i][0] == 'n')
                    nSearch = splitted[i].substring(1);
                if (splitted[i][0] == 'b')
                    bSearch = splitted[i].substring(1);
            }
        } else if (text != '') {
            dSearch = text.split(/[^\d]+/);
            if (dSearch.length == 1) {
                iSearch = +dSearch[0];
                dSearch = null;
            } else {
                dSearch.sort(function(a, b) { return b-a; });
            }
        }
            
        var filtered = [];
        console.log(nSearch, bSearch);
        for(var i=0; i<data.length; i++) {
            if (iSearch != null)
                i == iSearch && filtered.push(i);
            else if (dSearch != null) 
                arrayEquals(data[i].D, dSearch) && filtered.push(i);
            else if (nSearch != null || bSearch != null)
                (nSearch == null || data[i].n == nSearch) &&
                (bSearch == null || data[i].b == bSearch) &&
                 filtered.push(i);
            else
                filtered.push(i)
        }
        return filtered;
    
    }
    
    function setSearch(text) {
        state.filtered = filter(text);
        state.shown = 0;
        $('.search input').val(text);
        $('.result-list').html('');
        showResults(100);
    }
    
    function showResults(more) {
        var result = $('.result-list');
        var toShow = Math.min(state.shown+more, state.filtered.length)
        for(var i=state.shown; i<toShow; i++) {
            result.append(makeThumb(state.filtered[i]));
        }
        state.shown = toShow;
        
        $('.search-status .showing').text(state.shown);
        $('.search-status .total').text(state.filtered.length);
        
        if (state.shown == state.filtered.length)
            $('.search-status .show-more').hide();
        else
            $('.search-status .show-more').show();
    }
    
    function makeThumb(index) {
        var n = '<span class="nodes">n'+data[index].n+'</span>';
        var b = '<span class="cardinality">b'+data[index].b+'</span>';
        var el = $('<div class="item"><img src="thumbs/' + index + '.svg" /><div class="legend">' + n+b +'</div></div>');
        el.on('click', function() {
            setGraph(index);
        });
        return el;
    }
    
    $('.search button').on('click', function() { setSearch($('.search input').val()); });
    $('.search input').on('keydown', function(e) { if (e.which == 13) setSearch($('.search input').val()); });
    $('.search-status .show-more').on('click', function(e) { showResults(100); e.preventDefault(); return false; });
    $(window).bind('resize', function() { setGraph(state.id); });
    $('.search .clear').on('click', function() { setSearch(''); });
    
    var params = window.location.hash.substring(1).split('/');
    setGraph(+(params[0]||Math.floor(Math.random()*data.length)));
    setSearch(params[1]||'');
    
})();

var _gaq = _gaq || [];
_gaq.push(['_setAccount', 'UA-5988212-2']);
_gaq.push(['_setDomainName', 'none']);
_gaq.push(['_setAllowLinker', true]);
_gaq.push(['_trackPageview']);

(function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
})();
