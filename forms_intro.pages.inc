<?php
require_once (libraries_get_path('mandrill') .'/src/Mandrill.php');

/**
 * Implements hook_form().
 */
function forms_intro_form($node, &$form_state) {

  $form = array();

  $form['contact'] = array(
    '#type' => 'fieldset',
    '#title' => t('Contact us.'),
    '#description' => t('If you would like to contact us. Please enter your info below.')
        );

  $form['contact']['first_name']=array(
            '#type'=>'textfield',
            '#title'=>t('Enter your name'),
            '#description'=>t('Please enter first name.')
        );

  $form['contact']['last_name']=array(
      '#type'=>'textfield',
      '#title'=>t('Enter your Last name'),
      '#description'=>t('Please enter last name.')
        );

   $form['contact']['email']=array(
      '#type'=>'textfield',
      '#title'=>t('Enter your email'),
      '#description'=>t('Please enter email.'),
      '#required' => TRUE
        );

    $form['contact']['country']=array(
            '#type'=>'select',
            '#title'=>t('Select your country'),
            '#options'=>array('Canada','Mexico','UK','USA'),
            '#default_value' => 3
        );

    $form['contact']['body']=array(
      '#type'=>'textarea',
      '#title'=>t('Message'),
      '#description'=>t('Please enter your message here.')
        );

    $form['submit']=array(
        '#type'=>'submit',
        '#value'=>t('Submit')
        );

  return $form;
}

/**
 * Implements hook_form().
 */
function forms_intro_form_validate($form, &$form_state) {

  if(filter_var($form_state['values']['email'], FILTER_VALIDATE_EMAIL) == false) {
    form_set_error('email','Email field does not contain a vaild email address');
  }

  return $form;
}

/**
 * Implements hook_form_submit().
 */
function forms_intro_form_submit($form, $form_state) {

  $mandrill = new Mandrill('xv-O_PMc1N37IqdBfIhJqg');
  $name = $form_state['values']['first_name'] ." " . $form_state['values']['last_name'];
  $country = countyTranslate($form_state['values']['country']);
  $to = "jtredlich@gmail.com";

  $message = "Information has been submitted from $name.<br />";
  $message .= "It was submitted from $country.<br />";
  $message .= "You can email them back at {$form_state['values']['email']}.<br />";
  $message .= "There message was: <br />{$form_state['values']['email']}";

  try{

        $message = array(
                'subject' => 'Email Information Request.',
                'text' => $message,
                'from_email' => 'jtredlich@gmail.com',
                'from_name' => 'Yourself',
                'to' => array(
                        array(
                                'email' => $to,
                                'name' => $name, // optional
                                'type' => 'to' //optional. Default is 'to'. Other options: cc & bcc
                                )
                ),
        );

    $result = $mandrill->messages->send($message);
    //print_r($result); //only for debugging

    }

    catch(Mandrill_Error $e) {

      echo 'A mandrill error occurred: ' . get_class($e) . ' - ' . $e->getMessage();
      throw $e;
    }

  drupal_set_message("Your form has been submitted.");
}

function countyTranslate($c) {

  switch ($c){
    case 0:
      return "Canada";
      break;
    case 1:
      return "Mexico";
      break;
    case 2:
      return "UK";
      break;
    case 3:
      return "USA";
      break;
    default;
      return"Invalid Country";
      break;
  }
}
