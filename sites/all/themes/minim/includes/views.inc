<?php
/**
 * Preprocess and Helper Functions for Views
 **/

/**
 * Implements hook_preprocess_HOOK
 */
function minim_preprocess_views_view_unformatted(&$variables) {
  $rows_rendered = array();
  if (!empty($variables['rows'])) {
    foreach ($variables['rows'] AS $id => $row) {
      $complete_row = "<div class='" . $variables['classes_array'][$id] . "'>";
      $complete_row .= $row;
      $complete_row .= "</div>";
      $rows_rendered[] = array('row' => $complete_row);
    }
  }
  $variables['rows_rendered'] = $rows_rendered;
  $sub_functions = array();
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->name;
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->name . '__' . $variables['view']->current_display;
  foreach ($sub_functions AS $function) {
    if (function_exists($function)) {
      $function($variables);
    }
  }
}

/**
 * Implements hook_preprocess_HOOK
 */
function minim_preprocess_views_view_fields(&$variables) {
  $fields_rendered = '';
  if (!empty($variables['fields'])) {
    foreach ($variables['fields'] AS $id => $field) {
      // Seperator
      if (!empty($field->separator)) {
        $fields_rendered .= $field->separator;
      }
      $fields_rendered .= $field->wrapper_prefix; 
      $fields_rendered .= $field->label_html; 
      $fields_rendered .= $field->content;
      $fields_rendered .= $field->wrapper_suffix;


    }
  }
  $variables['fields_rendered'] = $fields_rendered;
  // Allow for more granular preproces_functions
  $sub_functions = array();
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->name;
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->name . '__' . $variables['view']->current_display;
  foreach ($sub_functions AS $function) {
    if (function_exists($function)) {
      $function($variables);
    }
  }
}

function minim_preprocess_views_view_fields__recent_work(&$v) {
 
  $row = $v['row'];

  $node_url = 'node/' . $row->nid;
  // Title
 // $v['title'] = l($row->node_title, $node_url);
  $v['title'] = $row->node_title;

  // Body 
  if (!empty($row->field_body[0]['raw']['summary'])) {
    $v['body'] = $row->field_body[0]['raw']['summary'];
  }
  else {
    $v['body'] = views_trim_text(array('max_length' => 200, 'html' => TRUE, 'ellipsis' => TRUE), $row->field_body[0]['raw']['value']);
  }
  // More Link
  $v['read_more_link'] = l('View Project', $node_url, array('attributes' => array('class' => array('more-link')))); 
  // Image
  if (!empty($row->field_field_image[0])) {
    $image = theme('image', array('path' => $row->field_field_image[0]['raw']['uri']));
    $v['image'] = l($image, $node_url, array('html' => TRUE));
  }
}


function minim_preprocess_views_view_fields__all_work(&$v) {

  $row = $v['row'];
  $node_url = 'node/' . $row->nid;
  // Title
  $v['title'] = l($row->node_title, $node_url);
  // Body 
  if (!empty($row->field_body[0]['raw']['summary'])) {
    $v['body'] = $row->field_body[0]['raw']['summary'];
  }
  else {
    $v['body'] = views_trim_text(array('max_length' => 75, 'html' => TRUE, 'ellipsis' => TRUE), $row->field_body[0]['raw']['value']);
  }
  // More Link
  $v['read_more_link'] = l('View Project', $node_url, array('attributes' => array('class' => array('more-link')))); 
  
  // date
  $v['date'] = $row->field_field_project_date;
}