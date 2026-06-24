/**
 * @author Jordan Locke
 * @version 0.1
 * @breif A front-end script that adds event listeners for buttons within the nav bar
 */
"use strict"

import { getHTML } from "./loadHTML.js";

$(document).ready(function(){

    $('.navBtn').click(function(){
        getHTML($(this).attr('data-page'));
    })

});